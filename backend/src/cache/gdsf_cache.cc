#pragma once

#include <stdio.h>
#include <cmath>
#include <map>
#include <vector>
#include "tsl/robin_map.h"

struct gd_object
{
    uint32_t key;
    uint32_t size;
    uint32_t hits;
    float score;

    uint8_t* data;
};

float gdsf(float base, float size, float freq)
{
    return base + (double(freq) / double(size));
}

class gd_ordered
{
    typedef std::multimap<double, gd_object> omap;
    typedef omap::iterator om_it;

    double min_score_;
    
    omap order_;
    tsl::robin_map<uint32_t, om_it> map_;

    Score sc;
    
    void evict(ssize_t size);

public:
    gd_cache(size_t capacity);
    
    void set(uint32_t key, uint32_t size);
    
    void* get(uint32_t key, uint32_t size);

    void clear();
};

void gdsf_cache::evict(ssize_t size)
{
    while (size > 0) {
        auto it = order_.begin();
        size -= it->second.size;
        used_ -= it->second.size;
        map_.erase(it->second.key);
        order_.erase(it);
    }
    
    min_score_ = order_.begin()->first;
}

void gdsf_cache::insert(uint32_t key, uint32_t size)
{
    if (size > capacity_)
        return;

    if (used_ + size > capacity_)
        evict(used_ + size - capacity_);
    
    map[key] = order_.insert({gdsf(min_score_, size, 1), kfs{key, size, 1}});
    used_ += size;
}

void gdsf_cache::test_round(uint32_t unix, uint32_t key, uint32_t size)
{
    (void)unix;
    auto it = map_.find(key);

    if (it != map_.end()) {
        kfs obj = it->second->second;
        order_.erase(it->second);
        ++obj.hits;

        it.value() = order_.insert({gdsf(min_score_, obj.size, obj.hits), obj});
        ++hits_;
    } else {
        insert(key, size);
    }

    ++counter_;
}

void gdsf_cache::clear()
{
    map_.clear();
    order_.clear();
    min_score_ = 0;
}
