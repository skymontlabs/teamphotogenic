// RatingModel.hpp
#ifndef RATINGMODEL_HPP
#define RATINGMODEL_HPP

struct pairwise_rating_model
{
    uint64_t rater_user_id;

    uint32_t winner_elo : 24;
    uint32_t winner_idx : 8;
    uint32_t loser_elo : 24;
    uint32_t loser_idx : 8;

    uint64_t rating_time;
}

#endif // RATINGMODEL_HPP

