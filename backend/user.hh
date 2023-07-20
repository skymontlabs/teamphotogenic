#pragma once

#include <vector>
#include <string_view>
#include <string>
#include "macros.hh"

enum permissions
{
    STANDARD,
    MODERATOR,
    ADMIN
};

enum age
{
    G18L24,
    G25L34,
    G35L44,
    G45
};

enum frequency
{
    HOURLY,
    DAILY,
    OCCASIONALLY,
    RARELY
};

enum speed
{
    REGULAR,
    QUICK,
    PRIORITY
};

enum auth_type
{
    EMAIL,
    PHONE,
    GOOGLE,
    FACEBOOK
};


struct notification
{
    uint64_t user;
    uint32_t task;
    uint32_t type;
    
    std::string serialize()
    {
        std::string out;
        
        if (task) {
            out.assign("Your task has finished with 123 votes");
        }
        
        return out;
    }
};


union user_stats {
    struct {
        uint32_t gender : 3;
        uint32_t age : 3;
        uint32_t permissions : 3;
    };
    
    uint32_t data32;
};

struct user
{
    user(std::string_view email_, const uint32_t permissions_):
    contact(email_),
    tasks(0,0),
    credits(0) {}
    
    std::string contact;
    auth_type mode;
    
    uint64_t password_idx;
    uint32_t spam_meter;
    uint32_t comments_approved;

    std::vector<uint64_t> tasks;
    std::vector<notification> notifications;
    std::vector<uint64_t> referrals;

    uint32_t credits;
    
    uint64_t original_referrer;
    std::string referral_code;
    
    user_stats st;
    
    std::string serialize()
    {
        std::string out = "{\"contact\":\"";
        out.append(contact);
        
        out.append("\",\"mode\":");
        out.append(itostr(mode));
        
        out.append(",\"gender\":");
        out.push_back(singledigit(st.gender));
        out.append(",\"age\":");
        out.push_back(singledigit(st.age));
        
        out.append(",\"credits\":");
        out.append(itostr(credits));
        
        out.push_back('}');

        return out;
    }
    
    
};
