//
//  rating.cpp
//  imagespro-backend
//
//  Created by Stephen Liang on 1/6/22.
//

#include "rating.hpp"
#include "itostr.hpp"

std::string rating::serialize()
{
    std::string out{"{"};
    out.append("\"vote\":");
    out.append(itostr(vote));
    out.append(",\"bitfield\":");
    out.append(itostr(bitfield));
    out.append(",\"comment\":\"");
    out.append(comment);
    out.append("\"}");
    
    return out;
}

size_t rating::serialize(uint8_t* out)
{
    
    *(uint32_t*)out = vote;
    out += 4;
    *(uint32_t*)out = bitfield;
    out += 4;
    *(uint32_t*)out = comment.length();
    out += 4;
    memcpy(out, comment.data(), comment.length());
    
    return out;
}
