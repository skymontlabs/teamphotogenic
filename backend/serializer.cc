//
//  serializer.cpp
//  imagespro-backend
//
//  Created by Stephen Liang on 1/6/22.
//

#include "dao.hh"

template <typename T>
static void write_data(std::string& fp, T* data, size_t size)
{
    std::ofstream fout(fp, ios::out | ios::binary);
    fout.write((const char*)data, size);
    
    fout.close();
}

std::string dao::serialize_map(std::unordered_map<std::string, uint64_t>& map)
{
    std::string v;
    
    for (auto it : map) {
        v.append(it.first);
        v.push_back(',');
        v.append(encode_ahex(it.second));
        v.push_back('\n');
    }
    
    return v;
}

std::string dao::serialize_users()
{
    std::string v;
    
    for (auto& u : users) {
        v.append(u.contact.data());
        v.push_back(',');
        v.push_back(0x30 | u.mode);
        v.push_back(',');
        v.append(encode_ahex(u.password_idx));
        v.push_back(',');
        v.append(encode_ahex(u.spam_meter));
        v.push_back(',');
        v.append(encode_ahex(u.comments_approved));
        v.push_back(',');
        
        v.append(encode_ahex(u.tasks.size()));
        v.append(",[");
        for (auto& t: u.tasks) {
            v.append(encode_ahex(t));
            v.push_back(',');
        }
        v[v.length() - 1] = ']';
        v.push_back(',');
        
        v.append(encode_ahex(u.tasks.size()));
        v.append(",[");
        for (auto& n: u.notifications) {
            v.append(n.serialize());
        }
        v[v.length() - 1] = ']';
        v.push_back(',');
        
        v.append(encode_ahex(u.tasks.size()));
        v.append(",[");
        for (auto& r: u.referrals) {
            v.append(encode_ahex(r));
        }
        v[v.length() - 1] = ']';
        v.push_back(',');

        v.append(encode_ahex(u.credits));
        v.push_back(',');
        
        v.append(encode_ahex(u.original_referrer));
        v.push_back(',');
                    
        v.push_back(u.st.data32);
        v.push_back('\n');
    }
    
    return v;
}

std::string dao::serialize_images()
{
    std::string v;
    
    for (auto& i : images) {
        
        // Which task this belongs to
        v.append(encode_ahex(i.task_id));
        v.push_back(',');
        
        // index in the queue
        v.append(encode_ahex(i.q_idx));
        v.push_back(',');
        
        // the URL or filepath where the file is.
        v.append(i.filepath);
        v.push_back(',');
        
        // list of ratings
        std::vector<rating> ratings;
        for (auto& r : ratings) {
            v.append(encode_ahex(r.user_id));
            v.append(r.comment);
            v.append(encode_ahex(r.data32));
        }
        v.push_back('\n');
    }
    
    return v;
}

std::string dao::serialize_tasks()
{
    std::string v;
    
    for (auto& t : tasks) {
        
        v.append(encode_ahex(t.user));
        v.push_back(',');
        v.append(encode_ahex(t.tv));
        v.push_back(',');
        v.append(encode_ahex(t.tc));
        v.push_back(',');
        v.append(encode_ahex(t.nv));
        v.push_back(',');
        
        v.append(encode_ahex(t.start_image));
        v.push_back(',');
        v.append(encode_ahex(t.end_image));
        v.push_back(',');
        v.append(encode_ahex(t.images_left));
        v.push_back('\n');
    }
    
    return v;
}

void dao::save()
{
    time_t ct = time(NULL);
    
    // serialize email_to_user
    {
        auto vec = serialize_map(email_to_user);
        auto fp = "/usr/share/ip/email/arch_" + itostr(save_idx) + "_" + itostr(ct);
        write_data(fp, vec.data(), vec.size());
    }
    
    // serialize phone_to_user
    {
        auto vec = serialize_map(phone_to_user);
        auto fp = "/usr/share/ip/phone/arch_" + itostr(save_idx) + "_" + itostr(ct);
        write_data(fp, vec.data(), vec.size());
    }
    
    // serialize referrers
    {
        auto vec = serialize_map(referrers);
        auto fp = "/usr/share/ip/refer/arch_" + itostr(save_idx) + "_" + itostr(ct);
        write_data(fp, vec.data(), vec.size());
    }
    
    // serialize users
    {
        auto vec = serialize_users();
        auto fp = "/usr/share/ip/users/arch_" + itostr(save_idx) + "_" + itostr(ct);
        write_data(fp, vec.data(), vec.length());
    }
    
    // serialize passwords
    {
        auto fp = "/usr/share/sex/aux_" + itostr(save_idx) + "_" + itostr(ct);
        write_data(fp, passwords.data(), passwords.size());
    }
    
    // serialize salts
    {
        auto fp = "/usr/share/sex/seg_" + itostr(save_idx) + "_" + itostr(ct);
        write_data(fp, salts.data(), salts.size());
    }
    
    // serialize tasks
    {
        auto vec = serialize_tasks();
        auto fp = "/usr/share/sex/task_" + itostr(save_idx) + "_" + itostr(ct);
        write_data(fp, vec.data(), vec.size());
    }
    
    // serialize images
    {
        auto vec = serialize_images();
        auto fp = "/usr/share/sex/imag_" + itostr(save_idx) + "_" + itostr(ct);
        write_data(fp, vec.data(), vec.size());
    }
    
    ++save_idx;
}
