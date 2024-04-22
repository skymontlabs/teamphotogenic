// RatingModel.hpp
#ifndef RATINGMODEL_HPP
#define RATINGMODEL_HPP

struct likert_rating_model
{
    uint64_t rater_user_id;

    uint64_t imageset_id;

    uint64_t rater_user_id;
    uint64_t rating_value : 3;
    
    uint64_t rating_time;
};

#endif // RATINGMODEL_HPP

