#include "dao.hh"


size_t dao::report_image(uint64_t user_id, uint64_t image_id)
{
    // if its in cleared, ignore it...
    auto cit = cleared_images.find(image_id);
    
    if (cit == cleared_images.end()) {
        if (image_id < images.size()) {
            auto it = reported_images_map.find(image_id);

            if (it != reported_images_map.end()) {
                it->second.reporters.push_back(user_id);
            } else {
                reported_images_map.insert({image_id, reported_image(images[image_id].task_id, image_id)});
            }
            
            return 0;
        }
    }
    
    return -1;
}

size_t dao::report_comment(uint64_t user_id, uint64_t image_id, uint64_t comment_id)
{
    // if its in cleared, ignore it...
    auto cit = cleared_comments.find((image_id << 16) | comment_id);
    
    if (cit == cleared_comments.end()) {
        if (image_id < images.size()) {
            reported_comments_map.insert({image_id, reported_comment(image_id, comment_id)});

            return 0;
        }
    }
    
    return -1;
}

std::string dao::get_reported_comments()
{
    std::string out = "[";
    
    for (auto it : reported_comments_map) {
        reported_comment rp = it.second;
        
        out.append(rp.serialize());
    }
    
    out[out.length()-1] = ']';
    
    return out;
}

std::string dao::get_reported_images()
{
    std::string out = "[";
    
    for (auto it : reported_images_map) {
        reported_image rp = it.second;
        
        out.append(rp.serialize());
    }
    
    out[out.length()-1] = ']';
    
    return out;
}

int dao::resolve_reported_image(uint64_t image_id)
{
    reported_images_map.erase(image_id);
    
    return -1;
}


int dao::resolve_reported_comment(uint64_t image_id, uint64_t comment)
{
    reported_comments_map.erase((image_id << 16) | comment);
    
    return -1;
}

void dao::trust_user(uint64_t id)
{
    ++users[id].comments_approved;
}

void dao::distrust_user(uint64_t id)
{
    users[id].comments_approved = 0;
}

