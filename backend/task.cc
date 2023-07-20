#include "task.hh"

size_t task::serialize_task(uint8_t* out)
{
    uint8_t* o = out;
    
    // total votes
    uint32_t total_votes = 0;
    uint32_t* total_votes_ptr = o;
    o += 4;
    
    // total comments
    uint32_t total_comments = 0;
    uint32_t* total_comments_ptr = o;
    o += 4;
 
    // num images
    
    // serialize each image
    for (int i = 0; i < image_list.size(); ++i) {
        // num votes
        uint32_t votes = image_list[i].votes.size();
        uint32_t comments = image_list[i].comments.size();

        // serialize image
        serstr(image_id);
        
        // serialize bar
        ser32(mean);
        ser32(votes);
        ser32(sem);

        // serialize histogram
        ser32(num_eh);
        ser32(num_decent);
        ser32(num_great);
        ser32(num_stunning);
        ser32(num_brilliant);

        // add votes and comments to the total
        total_votes += votes;
        total_comments += comments;
    }
    
    // serialize total
    *total_votes_ptr = total_votes;
    *total_comments_ptr = total_comments;
    
    return o - out;
}

std::string task::serialize(std::vector<image>& imgs, uint64_t idx)
{
    std::string out("{\"task_id\":\"");
    out.append(encode_ahex(idx));
    
    out.append("\",\"images\":");
    out.append(itostr(idx));
    
    out.append(",\"votes\":");
    out.append(itostr(idx));
    
    out.append(",\"comments\":");
    out.append(itostr(idx));
    
    out.append(",\"imgs\": [");
    for (auto i = start_image; i < end_image; ++i) {
        out.append(imgs[i].serialize_task(i));

        out += imgs[i].filepath;
        out += "\",";
    }
    out[out.length()-1] = ']';
    out.push_back('}');
    
    return out;
}


std::string task::serialize_mini(std::vector<image>& imgs, uint64_t idx)
{
    std::string out("{\"task_id\":\"");
    out.append(encode_ahex(idx));
    
    out.append("\",\"images\":");
    out.append(itostr(idx));
    
    out.append(",\"votes\":");
    out.append(itostr(idx));
    
    out.append(",\"comments\":");
    out.append(itostr(idx));
    
    // serialize 3
    uint32_t imsz = (min(3, uint32_t(end_image - start_image)));
    out.append(",\"imgs\": [");
    for (auto i = start_image; i < (start_image + imsz); ++i) {
        out.push_back('\"');
        out += imgs[i].filepath;
        out += "\",";
    }
    out[out.length()-1] = ']';
    out.push_back('}');
    
    return out;
}
