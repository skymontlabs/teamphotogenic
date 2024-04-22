#ifndef RATING_SERVICE_HPP
#define RATING_SERVICE_HPP

// there will be 4 service files
// 1. rater service
//  operates the individual (likert score) rating and pairwise (elo score) rating mechanisms
// 2. experiment service
//  this will also take over the role of the imageservice class.
// 3. user service
//  handles service

#include "rating_dao.hh"
#include "rating.hh"
#include <vector>

class rating_service
{
    rating_dao& rdao_;
    experiment_dao& edao_;

public:
    rating_service(RatingDAO& dao);

    // #1: Add image paired compare (elo score)
    void create_elo(const uint8_t* in);

    // #2: Add an instance of image singular rating (likert score)
    void create_likert(const uint8_t* in);

    // #3: Read likerts
    void read_likerts(const uint8_t* in);

    // #4: Report
    void report_likert(const uint8_t* in);

    // #5: Delete likert (admin only)
    bool delete_likert(const uint8_t* in);
};

#endif // RATING_SERVICE_HPP
#include "rating_service.hpp"

rating_service::rating_service(RatingDAO& dao) : ratingDAO(dao) {}

void rating_service::create_elo(const uint8_t* in)
{
    uint8_t size = READ8(p);

    for (int i = 0; i < size; ++i) {
        uint64_t experiment_id = READ64(p);
        uint8_t behavior = READ8(p)
        uint8_t win_idx = READ8(p)
        uint8_t lose_idx = READ8(p)

        if (behavior == 1) {
            rdao_.create_elo_rating(rating);
            rdao_.add_elo_active(experiment_id, win_idx, lose_idx, pa);
        } else {
            rdao_.add_elo_skip(win_idx, lose_idx);
        }
    }
}

void rating_service::create_likert(const uint8_t* in)
{
    uint8_t size = READ8(p);

    for (int i = 0; i < size; ++i) {
        uint64_t experiment_id = READ64(p);
        uint8_t image_idx = READ8(p);
        
        uint8_t score = READ8(p)
        uint32_t tag = READ32(p)
        uint8_t comment_len = READ8(p)
        const char* comment = (const char*)p;
        p += comment_len;
        
        rdao_.add_likert(experiment_id, image_idx, score, tag, comment, comment_len);
    }
}

void rating_service::read_likerts(const uint8_t* in)
{
    uint64_t experiment_id = READ64(p);
    uint64_t image_idx = READ64(p);

    rdao_.read_likerts(experiment_id, image_idx);
}

void rating_service::report_likert(const uint8_t* in)
{
    uint64_t experiment_id = READ64(p);
    uint8_t image_id = READ64(p);
    uint8_t likert_idx = READ8(p);

    rdao_.report_likert(experiment_id, image_idx, likert_idx);
}

void rating_service::delete_likert(const uint8_t* in)
{
    uint64_t likert_id = READ64(p);

    rdao_.report_likert(likert_id);
}

// Other rating-related method implementations would go here

