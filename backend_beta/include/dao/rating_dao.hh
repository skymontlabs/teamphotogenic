#ifndef RATINGDAO_HPP
#define RATINGDAO_HPP

#include <optional>
#include <string>
#include <vector>
#include "RatingModel.hpp"
#include "DatabaseConnector.hpp"

class rating_dao
{
    // Handle to the database connection
    database_connection* db_conn_;

    // Handle to the Redis cache connector
    //redis_connector* rs_conn_;

    image_model* get_img_locally(const uint64_t image_id);
    //image_model* get_img_redis(const uint64_t image_id);
    
    void cache_rtg_locally(const uint64_t image_id, const image_model& image);
    //void cache_rtg_redis(const uint64_t image_id, const image_model& image);

public:
    rating_dao(DatabaseConnector& db);
    
    bool create_rating(const RatingModel& rating);

    bool read_rating(const RatingModel& rating);

    bool report_rating(const RatingModel& rating);
    
    bool delete_rating(const uint64_t image_id, const RatingModel& rating);

    vector<RatingModel> getRatingsByImageId(const std::string& imageId);
    vector<RatingModel> getRatingsByUserId(const std::string& userId);
};

#endif // RATINGDAO_HPP
