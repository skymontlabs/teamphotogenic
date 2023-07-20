//
//  rating.hpp
//  imagespro-backend
//
//  Created by Stephen Liang on 1/6/22.
//

#ifndef rating_hpp
#define rating_hpp

#include <stdint.h>
#include <string>

struct rating
{
    uint64_t user_id;
    
    std::string comment;

    union {
        struct {
            uint32_t show : 1;
            uint32_t age : 3;           // [0:3]
            uint32_t frequency : 3;     // [3:6]
            uint32_t influence : 3;     // [3:6]
            uint32_t vote : 2;          // [9:11]
            uint32_t bitfield : 20;     // [11:31]
        };
        
        uint32_t data32;
    };
    
    
    rating(uint64_t user_id_, uint32_t vote_, uint32_t bitfield_, std::string_view comment_):
    user_id(user_id_),
    vote(vote_),
    bitfield(bitfield_),
    comment(comment_) {}
    
    std::string serialize();
    size_t serialize(uint8_t* out);
};

#endif /* rating_hpp */
