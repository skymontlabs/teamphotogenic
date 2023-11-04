#include "RatingService.hpp"

RatingService::RatingService(RatingDAO& dao) : ratingDAO(dao) {}

bool RatingService::addRating(const Rating& rating) {
    // Business logic to add a rating
    return ratingDAO.createRating(rating);
}

std::vector<Rating> RatingService::getRatingsForImage(const std::string& imageId) {
    // Business logic to retrieve ratings for a specific image
    return ratingDAO.getRatingsByImageId(imageId);
}

bool RatingService::updateRating(const Rating& rating) {
    // Business logic to update a rating
    return ratingDAO.updateRating(rating);
}

// Other rating-related method implementations would go here
