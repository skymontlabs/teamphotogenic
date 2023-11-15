// RatingModel.hpp
#ifndef RATINGMODEL_HPP
#define RATINGMODEL_HPP

#include <string>

class rating_model
{
    uint32_t image_id_;
    uint32_t user_id_;
    float rating_;

public:
    rating_model(uint32_t image_id, uint32_t user_id, float rating);

    uint32_t getImageId() const;
    uint32_t getUserId() const;
    float getRating() const;

    void setImageId(int id);
    void setUserId(int id);
    void setRating(float rating);

    // You might want to add more methods here, for example:
    // - To convert the object to a format suitable for database storage
    // - To calculate new ELO ratings after a comparison
    // - To serialize/deserialize the object for communication purposes

    size_t serialize(uint8_t* out);
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
