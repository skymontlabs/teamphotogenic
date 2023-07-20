#include <sodium.h>

#include "authenticator.hh"
#include "ahex.hh"
#include "dao.hh"
#include "email.hpp"
#include "cinatra.hpp"

#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

using namespace cinatra;

inline uint64_t twist(uint64_t x) {
    x ^= 0xdc348163;
    x += 0x4040;
    x <<= 1;
    x ^= 0x659a1760;
    
    return x;
}

inline uint64_t untwist(uint64_t x) {
    x ^= 0x659a1760;
    x >>= 1;
    x -= 0x4040;
    x ^= 0xdc348163;
    
    return x;
}

std::string serialize_vector(std::vector<std::string>& v)
{
    std::string out{"["};
    for (auto& x: v) {
        out += x;
        out.push_back(',');
    }
    out[out.length()-1] = ']';
    return out;
}

inline int get_task_and_image_id(uint64_t* tid, uint64_t* iid, const char* id_str)
{
    uint64_t task_id = decode_ahex(id_str, 16);
    uint64_t image_id = decode_ahex(id_str + 16, 16);
    
    if (task_id != 0 || image_id != 0)
        return -1;
    
    task_id = untwist(task_id);
    image_id = untwist(image_id);
    
    *tid = task_id;
    *iid = image_id;
    
    return 0;
}

int main(int argc, const char * argv[])
{
    authenticator au;
    dao d;

    //int max_thread_num = std::thread::hardware_concurrency();
    http_server server(1);
    server.listen("0.0.0.0", "8081");
    
    // get my tasks
    server.set_http_handler<GET>("/tasks", [&d, &au](request& req, response& res)
    {
        auto auth = req.get_header_value("Authorization");
        if (!auth.empty()) {
            // now check if token right
            userdata ud = au.verify_token(auth.data());
            if (ud.id == -1) {
                res.set_status_and_content(status_type::unauthorized, "Invalid token");
                return;
            }
            
            // get user
            uint64_t user_id = ud.id;
            auto user_id_str = req.get_query_value("user_id");
            if (!user_id_str.empty() && ud.permissions == ADMIN) {
                int v = decode_ahex_varint(user_id_str.data());
                if (v != -1) {user_id = v;}
            }
            
            std::string v = d.get_tasks(user_id);
            if (v.empty()) res.set_status_and_content(status_type::ok, std::string("no tasks"));
            else res.set_status_and_content(status_type::ok, std::move(v));
        } else {
            res.set_status_and_content(status_type::unauthorized, "Need token");
        }
    });
    
    
    
    // rate an image
    server.set_http_handler<POST>("/rate", [&d, &au](request& req, response& res)
    {
        auto auth = req.get_header_value("Authorization");
        if (!auth.empty()) {
            // now check if token right
            userdata ud = au.verify_token(auth.data());
            if (ud.id == -1) {
                res.set_status_and_content(status_type::unauthorized, "Invalid token");
                return;
            }
            
            auto id_str = req.get_query_value("id");
            if (id_str.empty()) {
                res.set_status_and_content(status_type::bad_request);
                return;
            }
            
            uint64_t task_id, image_id;
            if (get_task_and_image_id(&task_id, &image_id, id_str.data())) {
                res.set_status_and_content(status_type::not_found);
                return;
            }

            std::string_view v = req.body();
            if (!v.empty()) {
                // start parsing
                const uint8_t* p = (const uint8_t*)v.data();
                
                // get score
                uint8_t score = load8(p)
                uint16_t tags = load16(p)
                uint16_t note_len = load16(p)
                const char* note = (const char*)p;
                
                d.rate_image(task_id, image_id, ud.id, score, tags, std::string_view{note, note_len});
                
                std::string data = d.get_rate(ud.id);
                
                if (data.empty()) {
                    res.set_status_and_content(status_type::not_found, "no tasks...");
                } else {
                    res.set_status_and_content(status_type::ok, std::move(data));
                }
                
            } else {
                res.set_status_and_content(status_type::bad_request, "x123");
            }
            
        } else {
            res.set_status_and_content(status_type::unauthorized, "Need token");
        }
    });
    
    
    
    // skip an image
    server.set_http_handler<POST>("/skip", [&d, &au](request& req, response& res)
    {
        auto auth = req.get_header_value("Authorization");
        if (!auth.empty()) {
            // now check if token right
            userdata ud = au.verify_token(auth.data());
            if (ud.id == -1) {
                res.set_status_and_content(status_type::unauthorized, "Invalid token");
                return;
            }
            
            auto id_str = req.get_query_value("id");
            if (id_str.empty()) {
                res.set_status_and_content(status_type::bad_request);
                return;
            }
            
            uint64_t task_id = 0, image_id = 0;
            if (get_task_and_image_id(&task_id, &image_id, id_str.data())) {
                res.set_status_and_content(status_type::not_found);
                return;
            }
            
            d.skip(task_id, image_id, ud.id);
            
            std::string data = d.get_rate(ud.id);
            
            if (data.empty()) {
                res.set_status_and_content(status_type::not_found, "no tasks...");
            } else {
                res.set_status_and_content(status_type::ok, std::move(data));
            }
        } else {
            res.set_status_and_content(status_type::unauthorized, "Need token");
        }
    });
    
    
    // upload images
    server.set_http_handler<POST>("/upload", [&d, &au](request& req, response& res)
    {
        auto auth = req.get_header_value("Authorization");
        if (!auth.empty()) {
            userdata ud = au.verify_token(auth.data());
            if (ud.id == -1) {
                res.set_status_and_content(status_type::unauthorized, "Invalid token");
                return;
            }
            
            // check rate limiter
            auto imgs_str = req.get_query_value("imgs");
            int imgs = 0;
            if (!imgs_str.empty()) {
                imgs = 3;
                return;
            }
            
            // cloudinary sign urls
            std::vector<std::string> urls = cdn.sign_url(imgs);
            
            // return list of urls
            std::string ser = serialize_vector(urls);
            
            res.set_status_and_content(status_type::unauthorized, std::move(ser));
        } else {
            res.set_status_and_content(status_type::unauthorized, "Need token");
        }
    });
    
    
    
    // create a task
    server.set_http_handler<POST>("/task", [&d, &au](request& req, response& res)
    {
        auto auth = req.get_header_value("Authorization");
        if (!auth.empty()) {
            // now check if token right
            userdata ud = au.verify_token(auth.data());
            if (ud.id == -1) {
                res.set_status_and_content(status_type::unauthorized, "Invalid token");
                return;
            }
                
            std::string_view v = req.body();
            if (!v.empty()) {
                const char* p = v.data();
                
                // read standard preferences
                uint32_t gender = *p++;
                uint32_t age    = *p++;
                uint32_t votes  = *p++;
                if (gender >= 3 || age >= 5 || votes >= 100) {
                    res.set_status_and_content(status_type::bad_request, "invalid params");
                    return;
                }
                
                // read images
                std::vector<std::string> files;
                uint32_t image_ct = *p++;
                for (int i = 0; i < image_ct; ++i) {
                    // read each one into the database;
                    uint32_t url_len = *p++;
                    const char* url = p;
                    files.push_back(std::string{url, url_len});
                    
                    p += url_len;
                }
                
                uint64_t id = d.add_task(files, votes, age, gender, ud);
                
                std::string out = encode_ahex(id);
                res.set_status_and_content(status_type::created, std::move(out));
            } else {
                res.set_status_and_content(status_type::bad_request, "needs body");
            }
        } else {
            res.set_status_and_content(status_type::bad_request, "needs body");
        }
    });
    
    
    
    
    
    
    // login
    server.set_http_handler<POST>("/login", [&d, &au](request& req, response& res)
    {
        std::string_view v = req.body();
        if (!v.empty()) {
            const char* p = v.data();
            
            uint32_t email_len = *p++;
            const char* email = p;
            p += email_len;
            
            if (!verify_email({email, email_len})) {
                res.set_status_and_content(status_type::created, "invalid email");
            }
        
            uint8_t* password = (uint8_t*)p;
            if (v.length() != email_len + 64) {
                res.set_status_and_content(status_type::bad_request);
                return;
            }
            
            userdata ud = d.get_userdata(std::string_view{email, email_len}, password);
            std::string token = au.create_token(ud);
            
            res.set_status_and_content(status_type::ok, std::move(token));
        } else {
            res.set_status_and_content(status_type::bad_request, "no body");
        }
    });
    
    
    // signup
    server.set_http_handler<POST>("/signup", [&au, &d](request& req, response& res) {
        std::string_view v = req.body();
        if (!v.empty()) {
            const char* p = v.data();
            
            std::string_view contact;
            uint8_t* password;
            int email_or_phone = *p++;
            printf("%d\n", email_or_phone);
            
            if (email_or_phone == 'e') {
                uint32_t email_len = *p++;
                printf("%d\n", email_len);
                const char* email = p;
                p += email_len;
                
                if (!verify_email({email, email_len})) {
                    res.set_status_and_content(status_type::bad_request, "email failed");
                    return;
                }
                
                if (v.length() != email_len + 66) {
                    res.set_status_and_content(status_type::bad_request, "password failed");
                    return;
                }
                
                contact = std::string_view(email, email_len);
                password = (uint8_t*)p;
            } else {
                const char* phone = p;
                p += 10;
                
                if (v.length() != 75) {
                    res.set_status_and_content(status_type::bad_request, "password failed");
                    return;
                }
                
                contact = std::string_view(phone, 10);
                password = (uint8_t*)p;
            }
            
            
            uint64_t user_id = d.create_user(contact, password, STANDARD);
            if (user_id == -1) {
                res.set_status_and_content(status_type::bad_request, "create user");
                return;
            }
            
            std::string token = au.create_token(userdata{user_id, STANDARD});
            
            res.set_status_and_content(status_type::ok, std::move(token));
        } else {
            res.set_status_and_content(status_type::bad_request);
        }
    });
    
    
    
    
    
    // modify my account
    server.set_http_handler<PUT>("/user", [&au, &d](request& req, response& res) {

        userdata ud;
    
        auto auth = req.get_header_value("Authorization");
        if (!auth.empty()) {
            // now check if token right
            userdata ud = au.verify_token(auth.data());
            if (ud.id == -1) {
                res.set_status_and_content(status_type::unauthorized, "Invalid token");
                return;
            }
            
            uint64_t user_id = ud.id;
            auto user_id_str = req.get_query_value("user_id");
            if (!user_id_str.empty() && ud.permissions == ADMIN) {
                int v = decode_ahex_varint(user_id_str.data());
                if (v != -1) {user_id = v;}
            }
        
            std::string_view v = req.body();
            if (!v.empty()) {
                const char* p = v.data();
                
                uint32_t email_len = *p++;
                const char* email = (*p++ != 0) ? p : nullptr;
                if (email && !verify_email({email, email_len})) {
                    res.set_status_and_content(status_type::ok);
                    return;
                    
                }

                uint8_t* password = (*p++ != 0) ? (uint8_t*)p : nullptr;
                if (password) {
                    p += 64;
                }

                uint8_t age = *p++;
                uint8_t frequency = *p++;
                uint8_t permissions = *p++;
                
                int c = d.modify_user(user_id, std::string_view{email, email_len}, password, age, frequency, 0, permissions);
                
                if (c == 0) {
                    res.set_status_and_content(status_type::ok);
                } else {
                    res.set_status_and_content(status_type::not_modified);
                }
            } else {
                res.set_status_and_content(status_type::not_modified);
            }
        }
    });
    
    
    server.run();
    
    
    return 0;
}
