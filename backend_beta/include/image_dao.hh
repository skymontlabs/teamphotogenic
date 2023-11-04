#ifndef IMAGEDAO_HPP
#define IMAGEDAO_HPP

#include <unordered_map>
#include <optional>
#include <string>
#include <vector>

class image_dao
{
    database_connection* db_conn_; // Handle to the database connection
    redis_connector* rs_conn_; // Handle to the Redis cache connector
    gdsf_cache* lcache_; // Local in-memory cache


    void* db_get_image_callback(const CassResult* result, CassError code, void* data);

    image_model* get_img_locally(const uint64_t image_id);
    image_model* get_img_redis(const uint64_t image_id);
    
    void cache_img_locally(const uint64_t image_id, const image_model& image);
    void cache_img_redis(const uint64_t image_id, const image_model& image);
    // Other cache-related methods...

public:
    image_dao(database_connection* db_conn, redis_connector* rs_conn);
    ~image_dao();

    image_model getImageById(const uint64_t image_id);
    vector<image_model> getImagesByUserId(const uint64_t userId);

    int deleteImage(const uint64_t image_id);
};

#endif // IMAGEDAO_HPP
