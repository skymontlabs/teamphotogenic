#pragma once

#include <stdint.h>
#include <vector>
#include <string>
#include "macros.hh"

struct reported_image
{
    // task this occured on
    uint64_t task_id;
    
    // global image id this occured on
    uint64_t image_id;
    
    // which user id's reported this
    std::vector<uint64_t> reporters;
    
    reported_image(uint64_t task_id_, uint64_t image_id_):
    task_id(task_id_),
    image_id(image_id_) {}
    
    void serialize(uint8_t* out) const;
    
    // images[image_id].url;
};


// serialize comment text
// serialize imageid
// serialize comment_id

struct reported_comment
{
    // task this occured on
    uint64_t image_id : 48;
    
    // global image id this occured on
    uint64_t comment_id : 16;
    
    reported_comment(uint64_t image_id_, uint64_t comment_id_):
    image_id(image_id_),
    comment_id(comment_id_) {}
    
    std::string serialize() const;
};


std::string reported_image::serialize(uint8_t* out) const
{
    std::string out("{\"task_id\":\"");
    out += encode_ahex(task_id);
    out.append("\",\"comment_id\":\"");
    out += encode_ahex(image_id);
    
    return out;
}

std::string reported_comment::serialize(uint8_t* out) const
{
    std::string out("{\"image_id\":\"");
    out += encode_ahex(image_id);
    out.append("\",\"comment_id\":\"");
    out += encode_ahex(comment_id);
    out.append("\"}");
    
    return out;
}

