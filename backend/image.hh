#pragma once

#include <cstdint>
#include <vector>
#include <string_view>
#include <string>
#include <utility>
#include "macros.hh"
#include "rating.hpp"


struct image
{
    image(uint64_t task_id_, std::string& filepath_):
    task_id(task_id_),
    filepath(filepath_) {}
    
    // Which task this belongs to
    uint64_t task_id;
    
    // index in the queue
    uint64_t q_idx;
    
    // the URL or filepath where the file is.
    std::string filepath;
    
    // Who skipped this?
    std::vector<uint64_t> skipped;
    
    // list of ratings
    std::vector<rating> ratings;
        
    std::string serialize(uint64_t niid);
    std::string serialize_task(uint64_t niid);
    std::string serialize_rate(uint64_t niid);
};





static float calculate_std(std::vector<uint8_t>& votes, uint32_t summation)
{
    float var = 0.0f;
    float mean = float(summation) / votes.size();
    
    for (auto i : votes) {
        float diff = (float(i) - mean);
        var += (diff * diff);
    }
    
    float std = sqrt(var / votes.size());
    
    return std;
}


std::string image::serialize(uint64_t niid)
{
    uint32_t score = 0;
    std::vector<uint8_t> votes;
    std::vector<std::string> comments;
    
    for (auto& r : ratings) {
        score += r.vote;
        votes.push_back(r.vote);
        comments.push_back(r.comment);
    }

    std::string out = "{\"id\":\"";
    out += encode_ahex(task_id);
    out += encode_ahex(niid);

    out.append("\",\"url\":\"");
    out.append(filepath);

    out.append("\",\"score\":");
    out.append(itostr(score));

    out.append(",\"std\":");
    out.append(std::to_string(calculate_std(votes, score)));

    out.append("\",\"votes\":");
    out.append(itostr(votes.size()));

    out.append("\",\"comments\":[");
    for (auto& c : comments) {
        out.append("\"");
        out.append(c);
        out.append("\"");
    }
    out.append("]");
    
    return out;
}

std::string image::serialize_task(uint64_t niid)
{
    std::string out = "{\"id\":\"";

    out += encode_ahex(task_id);
    out += encode_ahex(niid);

    uint32_t sum = 0;
    uint32_t comments = 0;
    for (auto& r: ratings) {
        sum += ((1 + r.vote) << 1);
        comments += (!r.comment.empty());
    }

    out.append("\",\"url\":\"");
    out.append(filepath);
    
    out.append("\",\"score\":");
    out.append(itostr(sum));
    
    out.append(",\"votes\":");
    out.append(itostr(uint32_t(ratings.size())));
    
    out.append(",\"comments\":\"");
    out.append(itostr(comments));
    
    out.append("\"}");

    return out;
}

std::string image::serialize_rate(uint64_t niid)
{
    std::string out = "{\"id\":\"";

    out += encode_ahex(task_id);
    out += encode_ahex(niid);

    out.append("\",\"url\":\"");
    out.append(filepath);
    out.append("\"}");

    return out;
}
