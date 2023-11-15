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

class RatingService
{
    experiment_dao& edao_;

public:
    RatingService(RatingDAO& dao);

    // Add image paired compare (elo score)
    bool add_elo(const uint8_t* in);

    // Add an instance of image singular rating (likert score)
    bool add_likert(const uint8_t* in);

    // Skip
    bool skip_elo(const uint8_t* in);

    // Skip a 
    bool skip_likert(const uint8_t* in);

    // Report
    bool report_likert(const uint8_t* in);

    // Report
    bool report_elo(uint32_t);
};

#endif // RATING_SERVICE_HPP
