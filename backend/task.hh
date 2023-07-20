#pragma once

#include <stdint.h>
#include <vector>
#include "macros.hh"
#include "image.hh"
#include "ahex.hh"
#include "itostr.hpp"

enum task_status
{
    RUNNING,
    PAUSED_MANUAL,
    PAUSED_NONSUFFICIENT,
    FINISHED
};

struct task
{
    task(uint64_t user_, uint32_t nv_, uint64_t start_, uint64_t end_):
    user(user_),
    nv(nv_),
    start_image(start_),
    end_image(end_),
    images_left(uint32_t(end_-start_)){}

    uint64_t user;
    uint32_t tv;
    uint32_t tc;
    uint32_t nv;
    
    uint64_t start_image;
    uint64_t end_image;
    uint32_t images_left;

    task_status status;
    
    std::string serialize(std::vector<image>& imgs, uint64_t idx);
    
    std::string serialize_mini(std::vector<image>& imgs, uint64_t idx);
};
