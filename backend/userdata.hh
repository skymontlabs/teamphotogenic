#pragma once

#include <cstdint>

struct userdata
{
    userdata(uint64_t id=-1, int32_t permissions=0):
    id(id),
    permissions(permissions) {}
    
    uint64_t id;
    uint32_t permissions : 2;
    uint32_t credits : 23;
    
    uint32_t gender : 3;
    uint32_t age : 3;
    uint32_t time : 3;
    uint32_t frequency : 3;
    uint32_t influence : 3;
    
    
    uint32_t fast : 1;
    uint32_t simultaneous : 1;
    uint32_t reports : 1;

    
    uint32_t is_app : 1;
    
    time_t last_used;
};
