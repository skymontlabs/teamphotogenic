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
