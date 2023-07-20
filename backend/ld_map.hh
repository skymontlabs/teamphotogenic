#pragma once

#include "hash_map.hpp"
#include <string>

template <typename V, int l0, int l1, int l2>
class ld_map
{
    emilib::HashMap<std::string, V> lt0_map_;
    emilib::HashMap<std::string, V> lt1_map_;
    emilib::HashMap<std::string, V> lt2_map_;
    emilib::HashMap<std::string, V> varlen_map_;

public:

    void insert(std::string& key, V val)
    {
        uint32_t len = uint32_t(key.length());
        
        if (len < l0) {
            lt0_map_.insert(key, val);
        } else if (len < l1) {
            lt1_map_.insert(key, val);
        } else if (len < l2) {
            lt2_map_.insert(key, val);
        } else {
            varlen_map_.insert(key, val);
        }
    }
    
    typename emilib::HashMap<std::string, V>::iterator find(std::string& key)
    {
        uint32_t len = uint32_t(key.length());
        
        if (len < l0) {
            return lt0_map_.find(key);
        } else if (len < l1) {
            return lt1_map_.find(key);
        } else if (len < l2) {
            return lt2_map_.find(key);
        } else {
            return varlen_map_.find(key);
        }
    }
};
