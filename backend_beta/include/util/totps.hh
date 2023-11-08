#pragma once

#include <sodium.h>
#include <unordered_map>
#include <cstdint>
#include <string>
#include "userdata.hh"
#include "ahex.hh"

class authenticator
{
    std::unordered_map<std::string, userdata> cookie_to_id;

public:
    authenticator() {}
    
    std::string create_token(userdata ud)
    {
        uint8_t bin[24];
        randombytes_buf(bin, 24);
        
        cookie_to_id.insert({std::string{(const char*)bin, 24}, ud});
        return encode_ahex(bin, 24);
    }
    
    void remove_token(const char* code)
    {
        cookie_to_id.erase(std::string{(const char*)code, 24});
    }

    userdata verify_token(const char* code)
    {
        uint8_t out[24];
        if (decode_ahex(out, code, 48) != 0)
            return userdata(-1,-1);

        auto it = cookie_to_id.find(std::string{(const char*)out, 24});
        if (it == cookie_to_id.end())
            return userdata(-1,-1);
        
        if (it->second.last_used > time(NULL) + 3600)
            return userdata(-1,-1);
        
        puts("we made it");
        
        return it->second;
    }
};
