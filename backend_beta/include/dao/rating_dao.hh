#ifndef RATINGDAO_HPP
#define RATINGDAO_HPP

#include <optional>
#include <string>
#include <vector>
#include "rating_model.hpp"
#include "DatabaseConnector.hpp"

class rating_dao
{
    // Handle to the database connection
    database_connection* db_conn_;

    //pending_ratings

    // Bloom filter
    bloom_filter* bloom_;

    // cache rating in server
    void cache_rtg_locally(const uint64_t image_id, const image_model& image);

public:
    // Class is for database only
    rating_dao(database_connection* db_conn);

    // Give elo rating to image
    int64_t create_elo_rating(const elo_model& rating, cbk_data& cbk);

    // Give likert rating to image
    int64_t create_likert_rating(const likert_model& rating, cbk_data& cbk);

    // Read ratings for image
    int64_t read_ratings_by_image(uint8_t* out, const uint64_t image_id, cbk_data& cbk);

    // Read rating by user
    int64_t read_ratings_by_user(uint8_t* out, const uint64_t user_id, cbk_data& cbk);

    // Reports comment, but puts whole rating into question
    int64_t report_rating(const uint64_t rating_id, cbk_data& cbk);

    // Deletes rating (admin only behavior)
    int64_t delete_rating(const uint64_t rating_id, cbk_data& cbk);

};

#endif // RATINGDAO_HPP
