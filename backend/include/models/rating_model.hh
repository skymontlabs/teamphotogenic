// RatingModel.hpp
#ifndef RATINGMODEL_HPP
#define RATINGMODEL_HPP

#include <string>

class elo_rating_model
{
    uint32_t image_idx_;
    uint64_t experiment_id_;
    uint64_t user_id_;

    uint8_t winner_idx_;
    uint8_t loser_idx_;
    int winner_elo_;
    int loser_elo_;

public:
    elo_rating_model(uint32_t image_id, uint32_t user_id, float rating);

    size_t elo_rating_model::serialize(uint8_t* out)
    {
        
    }
}

class likert_rating_model
{
    uint64_t user_id;
    uint64_t experiment_id;
    uint32_t image_idx_;
    float rating_;

public:
    likert_rating_model(uint32_t image_id, uint32_t user_id, float rating);

    uint32_t get_imageid() const
    {
        return image_id;
    }

    uint32_t get_userid() const
    {
        return user_id;
    }

    float get_rating() const
    {
        return rating_;
    }

    // You might want to add more methods here, for example:
    // - To convert the object to a format suitable for database storage
    // - To calculate new ELO ratings after a comparison
    // - To serialize/deserialize the object for communication purposes

    size_t likert_rating_model::serialize(uint8_t* out)
    {

    }
};

#endif // RATINGMODEL_HPP


RatingModel::RatingModel(int image_id, int user_id, float rating):
image_id(image_id),
user_id(user_id),
rating(rating) {}

int RatingModel::getImageId() const
{
    return image_id;
}

int RatingModel::getUserId() const
{
    return user_id;
}

float RatingModel::getRating() const
{
    return rating;
}

void RatingModel::setImageId(int id)
{
    image_id = id;
}

void RatingModel::setUserId(int id)
{
    user_id = id;
}

void RatingModel::setRating(float new_rating)
{
    rating = new_rating;
}
