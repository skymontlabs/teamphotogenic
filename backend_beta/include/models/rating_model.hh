// RatingModel.hpp
#ifndef RATINGMODEL_HPP
#define RATINGMODEL_HPP

#include <string>

class rating_model
{
    int image_id;
    int user_id;
    float rating;

public:
    rating_model(int image_id, int user_id, float rating);

    int getImageId() const;
    int getUserId() const;
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
