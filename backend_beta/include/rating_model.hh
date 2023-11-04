// RatingModel.hpp
#ifndef RATINGMODEL_HPP
#define RATINGMODEL_HPP

#include <string>

class RatingModel {
public:
    RatingModel(int image_id, int user_id, float rating);

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

private:
    int image_id;
    int user_id;
    float rating; // Assuming a Likert scale rating; use an appropriate type for ELO or other systems
};

#endif // RATINGMODEL_HPP
