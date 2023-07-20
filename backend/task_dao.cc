#include "dao.hh"
#include <chrono>
#include <iostream>
#include <sys/time.h>
#include <ctime>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

int dao::pause_task(task& t)
{
    t.status = PAUSED_MANUAL;
    
    for (auto i = t.start_image; i < t.end_image; ++i) {
        evict_from(image_queue, i);
    }
    
    
    return 0;
}

int dao::rate_image(uint64_t task_id, uint64_t image_id, uint64_t rater,
                    uint8_t score, uint32_t bitfield, std::string_view note)
{
    task& t = tasks[task_id];
    image& im = images[image_id];
    user& iu = users[t.user];
    user& ou = users[rater];
    
    if (iu.credits) {
        // check if spam
        auto it = last_rated.find(rater);
        if (it == last_rated.end()) {
            time_t last = it->second;
            time_t cur = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

            // if diff is less than 350 ms, we consider it spammy.
            if (cur < (last + 350)) {
                return -2;
            }
        }
        
        im.ratings.push_back(rating{rater, score, bitfield, note});
        
        // deduct credits
        iu.credits--;

        // how many credits to give the rater
        uint32_t credits_add = 1;
        if (bitfield) {
            ++credits_add;
        } else if (note.length() < 32) {
            credits_add += 2;
        } else if (note.length() >= 32) {
            credits_add += 3;
        }

        ou.credits += credits_add;
        
        
        // is this image done
        if (im.ratings.size() >= t.nv) {
            //finish_image(t, iu, ou, im, image_id);
        }
        
        
        return 0;
    }
    
    return -1;
}


uint64_t dao::add_task(std::vector<std::string>& imagelist, uint32_t vpi, uint32_t age, uint32_t gender, userdata ud)
{
    
    uint64_t user_id = ud.id;
    
    // speed is always priority if user has upgrade
//    speed = (ud.fast == PRIORITY) ? 2 : speed;
    uint64_t cur_tskidx = tasks.size();
    uint64_t cur_imgidx = images.size();
    uint64_t end = cur_imgidx + imagelist.size();
    
    for (std::string& s : imagelist) {
        image im{cur_tskidx, s};
        images.push_back(im);
    }
    
    task t(user_id, vpi, cur_imgidx, end);
    tasks.push_back(t);
    
    add_to(image_queue, cur_imgidx, end);

    
    return cur_imgidx;
}


std::string dao::get_rate(uint64_t rater)
{
    uint64_t total = 0;
    
    for (auto i = idx0; i < image_queue.size(); ++i) {
        uint64_t niid = image_queue[idx0];
        image& im = images[niid];
        bool use = true;
        
        for (int j = 0; j < im.ratings.size(); ++j) {
            if (im.ratings[i].user_id == rater) {
                use = false;
                break;
            }
        }
        
        if (use) {
            return im.serialize_rate(niid);
        }  else if (i >= image_queue.size() && total < image_queue.size()) {
            i = 0;
        } else {
            return std::string();
        }
        
        ++total;
    }
    
    return std::string();
}

std::string dao::get_tasks(uint64_t user_id)
{
    user& u = users[user_id];
    if (u.tasks.size()) {
        auto utsk = u.tasks;
        std::string out("[");
        
        for (auto idx : utsk) {
            auto& t = tasks[idx];
            out.append(t.serialize_mini(images, idx));
            out.push_back(',');
        }
        out[out.length()-1] = ']';
        
        return out;
    }
    
    return std::string();
}

std::string dao::get_task(uint64_t task_id, userdata ud)
{
    if (tasks.size() > task_id) {
        task& t = tasks[task_id];
        
        if (t.user == ud.id || ud.permissions == ADMIN) {
            std::string out = t.serialize(images, task_id);
            
            return out;
        }
    }
    
    return std::string();
}




int dao::delete_task(uint64_t task_id, userdata ud)
{
    uint64_t user_id = ud.id;

    if (tasks[task_id].user == user_id || ud.permissions >= MODERATOR) {
        std::vector<uint64_t>& task_idxs = users[user_id].tasks;
        
        for (uint64_t idx : task_idxs) {
            task& t = tasks[idx];
            pause_task(t);
        }
        
        task_idxs.erase(std::remove(task_idxs.begin(), task_idxs.end(), task_id), task_idxs.end());
     }

    return 0;
}


int dao::delete_tasks(uint64_t user_id)
{
    std::vector<uint64_t>& task_idxs = users[user_id].tasks;
    user& u = users[user_id];
    
    for (uint64_t idx : task_idxs) {
        task& t = tasks[idx];
        pause_task(t);
    }
    
    u.tasks.clear();
    
    return 0;
}



int dao::skip(uint64_t task_id, uint64_t image_id, uint64_t rater)
{
    image& im = images[image_id];
    if (im.task_id != task_id) return -1;
    
    for (auto r : im.skipped) {
        if (r == rater)
            return -1;
    }
    
    images[image_id].skipped.push_back(rater);
    
    return 0;
}



uint64_t dao::create_user(std::string_view email, uint8_t* password, uint32_t permissions)
{
    auto it = email_to_user.find(std::string(email));
    
    if (it == email_to_user.end()) {
        email_to_user.insert({std::string(email), uint64_t(users.size())});
        users.push_back(user(email, permissions));
        return users.size();
    }
    
    return -1;
}


void dao::evict_from(std::vector<uint64_t>& im, uint64_t id)
{
    im[images[id].q_idx] = im.back();
    im.pop_back();
}

void dao::evict_from(uint64_t idx, uint32_t speed)
{
    evict_from(image_queue, idx);
}

void dao::replace(std::vector<uint64_t>& im, uint64_t idx, uint64_t nv)
{
    im[idx] = nv;
}

void dao::replace(uint64_t idx, uint64_t nv, uint32_t speed)
{
    replace(image_queue, idx, nv);
}

void dao::add_to(std::vector<uint64_t>& im, uint64_t id)
{
    im.push_back(id);
}

void dao::add_to(std::vector<uint64_t>& im, uint64_t start, uint64_t end)
{
    for (uint64_t i = start; i < end; ++i) {
        im.push_back(i);
    }
}

void dao::finish_image(task& t, user& iu,  image& im, uint64_t image_id)
{
    // check if there are any more images to rate
    
    --t.images_left;
    evict_from(im.q_idx, 0);
    
    if (!t.images_left) {
        // finish task
        t.status = FINISHED;
    }
    
    im.q_idx = -1;
}
