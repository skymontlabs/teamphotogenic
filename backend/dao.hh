#ifndef dao_h
#define dao_h

#include <cstdint>
#include <vector>
#include <unordered_map>
#include "itostr.hpp"
#include <string>
#include "task.hh"
#include "image.hh"
#include "user.hh"
#include "userdata.hh"
#include "macros.hh"
#include "ahex.hh"
#include <string>
#include <sodium.h>
#include "curler.hpp"
#include "flagged.hpp"
#include <unordered_map>
#include <fstream>
#include <ios>

using std::ios;

class dao
{
    struct reset {
        reset(uint64_t user_, uint64_t created_):
        user(user_),
        created(created_) {}
        
        uint64_t user;
        uint64_t created;
    };
    
    
    // admin list
    hat_trie<uint64_t> email_to_user;
    hat_trie<uint64_t> phone_to_user;
    hat_trie<reset> resets;
    hat_trie<uint64_t> referrers;

    vector<user> users;
    vector<uint8_t> passwords;
    vector<uint8_t> salts;
    
    // task list
    flat_map<uint64_t, time_t> last_rated;

    vector<uint64_t> image_queue;
    vector<task> tasks;
    vector<image> images;

    uint64_t idx0;
    
    // saving
    uint64_t save_idx;

    // flagged
    flat_map<uint64_t, reported_image> reported_images_map;
    flat_map<uint64_t, reported_comment> reported_comments_map;
    flat_map<uint64_t, reported_image> cleared_images;
    flat_map<uint64_t, reported_comment> cleared_comments;

    curler crl;
    
    void evict_from(std::vector<uint64_t>& im, uint64_t id);
    void evict_from(uint64_t idx, uint32_t speed);
    void replace(std::vector<uint64_t>& im, uint64_t idx, uint64_t nv);
    void replace(uint64_t idx, uint64_t nv, uint32_t speed);
    void add_to(std::vector<uint64_t>& im, uint64_t id);
    void add_to(std::vector<uint64_t>& im, uint64_t start, uint64_t end);
    void finish_image(task& t, user& iu, image& im, uint64_t image_id);
    
    void restore();
    void save();
    std::string serialize_map(flat_map<std::string, uint64_t>& map);
    std::string serialize_users();
    std::string serialize_images();
    std::string serialize_tasks();
public:
    dao() {}
    
    
    
    size_t reset_password(std::string id, uint8_t* password);
    size_t create_reset(std::string_view contact, int type);
    
    
    
    
    size_t report_image(uint64_t user_id, uint64_t image_id);
    size_t report_comment(uint64_t user_id, uint64_t image_id, uint64_t comment_id);
    
    std::string get_reported_comments();
    std::string get_reported_images();
    
    
    int resolve_reported_comment(uint64_t image_id, uint64_t comment);
    int resolve_reported_image(uint64_t image_id);
    
    
    
    
    
    uint64_t add_task(std::vector<std::string>& imagelist, uint32_t vpi, uint32_t age, uint32_t gender, userdata ud);
    int pause_task(task& t);
    int delete_task(uint64_t task_id, userdata ud);
    int delete_tasks(uint64_t user_id);
    int rate_image(uint64_t task_id, uint64_t image_id, uint64_t rater,
                   uint8_t score, uint32_t bitfield, std::string_view note);
    
    std::string get_rate(uint64_t rater);
    int skip(uint64_t task_id, uint64_t image_id, uint64_t rater);
    
    std::string get_tasks(uint64_t user_id);
    std::string get_task(uint64_t task_id, userdata ud);
    
    
    
    
    
    
    void trust_user(uint64_t id);
    void distrust_user(uint64_t id);
    
    user get_user(uint64_t id);
    userdata get_userdata(std::string_view email, const uint8_t* password);
    
    uint64_t get_user(uint8_t* out, uint32_t id, userdata ud);
    uint64_t create_user(std::string_view email, uint8_t* password, uint32_t permissions);
    
    int init_preferences(uint64_t user_id, user_stats st);
    int modify_user(uint64_t user_id, std::string_view email, uint8_t* password,
                    int age, int frequency, uint32_t credits, uint32_t permissions);
    
    void disable_user(uint64_t user_id);
    void delete_user(uint64_t user_id);
    void add_feature(uint64_t user_id, uint32_t f);
    
};

#endif /* dao_h */
