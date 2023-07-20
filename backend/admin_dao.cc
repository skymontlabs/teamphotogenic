#include "dao.hh"
#include "ahex.hh"
#include <sodium.h>

static bool hash_password(uint8_t* hash, const uint8_t* password, const uint8_t* salt)
{
    return crypto_pwhash_argon2id(hash, 64, (const char*)password, 64, salt, crypto_pwhash_OPSLIMIT_MIN, crypto_pwhash_MEMLIMIT_MIN, crypto_pwhash_ALG_ARGON2ID13);
}

static bool verify_password(const uint8_t* correct, const uint8_t* password, const uint8_t* salt)
{
    uint8_t hash[64];
    
    if (hash_password(hash, password, salt) != 0) {
        return -1;
    }
    
    return memcmp(correct, hash, 64);
}

userdata dao::get_userdata(std::string_view email, const uint8_t* password)
{
    auto it = email_to_user.find(std::string(email));
    if (it == email_to_user.end())
        return userdata{};
    
    uint64_t idx = it->second;
    
    const uint8_t* correct = &passwords[idx << 6];
    const uint8_t* salt = &salts[idx << 6];
    
    
    if (verify_password(correct, password, salt)) {
        user& u = users[idx];
        return userdata(idx, u.st.permissions);
    }
    
    return userdata();
}

int dao::modify_user(uint64_t user_id, std::string_view email, uint8_t* password,
                int age, int frequency, uint32_t credits, uint32_t permissions)
{
    user& u = users[user_id];
    
    if (!email.empty() && u.mode) {
        auto it = email_to_user.find(std::string(email));
        if (it != email_to_user.end()) {
            return -1;
        } else {
            u.contact = email;
        }
    } else {
        auto it = phone_to_user.find(std::string(email));
        if (it != phone_to_user.end()) {
            return -1;
        } else {
            u.contact = email;
        }
    }
    
    if (password != nullptr) {
        uint8_t hash[64];
        uint8_t* correct = &passwords[user_id << 6];
        uint8_t* salt = &salts[user_id << 6];
        
        if (verify_password(correct, password, salt)) {
            if (hash_password(hash, password, salt) != 0) {
                return -1;
            }
            
            memcpy(correct, hash, 64);
            return 0;
        }
    }
    
    if (age > uint32_t(G45 - G18L24)) {
        u.st.age = age;
    }
    
    
    if (permissions > uint32_t(ADMIN - STANDARD)) {
        u.st.permissions = permissions;
    }
    
    if (credits) {
        u.credits = credits;
    }
    
    return 0;
}

void dao::disable_user(uint64_t user_id)
{
    users[user_id].st.permissions = -1;
}


void dao::delete_user(uint64_t user_id)
{
    users[user_id].st.permissions = -2;
    email_to_user.erase(users[user_id].contact);
}

void dao::add_feature(uint64_t user_id, uint32_t f)
{/*
    if (user_id < users.size()) {
        switch (f) {
            case 1:
                users[user_id].st.faster = 1;
                break;
            case 2:
                users[user_id].st.simultaneous = 1;
                break;
            case 3:
                users[user_id].st.reports = 1;
                break;
        }
    }*/
}

size_t dao::create_reset(std::string_view contact, int type)
{
    std::unordered_map<std::string, uint64_t>& map = (type) ? email_to_user : phone_to_user;
    
    auto it = map.find(std::string(contact));
    if (it != map.end()) {
    
        uint8_t bin[24];
        randombytes_buf(bin, 24);
        
        resets.insert({std::string{(const char*)bin, 24}, reset(it->second, time(NULL))});
        std::string ahex = encode_ahex(bin, 24);
        
        
        crl.send_email(contact, ahex, 0);
        //crl.send_text(contact, key, 0);
        return 0;
    }
    
    return -1;
}

size_t dao::reset_password(std::string id, uint8_t* password)
{
    auto it = resets.find(id);
    if (it != resets.end()) {
        reset& r = it->second;
        
        if (r.created < time(NULL) - 3600) {
            uint8_t* password = &passwords[users[r.user].password_idx << 6];
            uint8_t* salt = &salts[users[r.user].password_idx << 6];
            
            uint8_t hash[64];
            if (hash_password(hash, password, salt) != 0) {
                return -1;
            }
            
            memcpy(&passwords[users[r.user].password_idx << 6], password, 64);
            return 0;
        } else {
            return -1;
        }
    }
    
    return -1;
}

int dao::init_preferences(uint64_t user_id, user_stats st)
{
    if (user_id < users.size()) {
        user& u = users[user_id];
        
        u.st.gender = u.st.gender;
        u.st.age = u.st.age;
        
        return 0;
    }
    
    return -1;
}
