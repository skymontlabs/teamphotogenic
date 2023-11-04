#ifndef RATING_SERVICE_HPP
#define RATING_SERVICE_HPP

#include "RatingDAO.hpp"
#include "Rating.hpp"
#include <vector>

class RatingService {
public:
    RatingService(RatingDAO& dao);

    bool addRating(const Rating& rating);
    std::vector<Rating> getRatingsForImage(const std::string& imageId);
    bool updateRating(const Rating& rating);
    // Additional methods related to ratings can be added here

private:
    RatingDAO& ratingDAO;
};

#endif // RATING_SERVICE_HPP
