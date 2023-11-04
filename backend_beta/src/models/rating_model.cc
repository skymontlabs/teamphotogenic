
// RatingModel.cpp
#include "RatingModel.hpp"

RatingModel::RatingModel(int image_id, int user_id, float rating)
    : image_id(image_id), user_id(user_id), rating(rating) {}

int RatingModel::getImageId() const {
    return image_id;
}

int RatingModel::getUserId() const {
    return user_id;
}

float RatingModel::getRating() const {
    return rating;
}

void RatingModel::setImageId(int id) {
    image_id = id;
}

void RatingModel::setUserId(int id) {
user_id = id;
}

void RatingModel::setRating(float new_rating) {
    rating = new_rating;
}

// Additional methods as necessary...
