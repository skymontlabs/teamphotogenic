#ifndef IMAGEDAO_HPP
#define IMAGEDAO_HPP

#include <unordered_map>
#include <optional>
#include <string>
#include <vector>

class user_dao
{
    // Handle to the database connection
    database_connection* db_conn_;

    // Handle to the Redis cache connector
    redis_connector* rs_conn_;

    // Local in-memory cache
    gdsf_cache* lcache_;

    image_model* get_usr_locally(const uint64_t image_id);
    image_model* get_usr_redis(const uint64_t image_id);
    
    void set_usr_locally(const uint64_t image_id, const image_model& image);
    void set_usr_redis(const uint64_t image_id, const image_model& image);
    // Other cache-related methods...
    
public:
    user_dao(database_connection* db_conn, redis_connector* rs_conn, gdsf_cache* lcache);

    ~user_dao();

    // Read user
    int32_t read_user(const uint64_t image_id);

    // Read users (admin only)
    int32_t read_users(const uint64_t limit, const uint64_t offset);

    // Register user
    int32_t register_user(const uint64_t image_id);

    // Create user (admin only)
    int32_t register_user(const uint64_t image_id);

    // Delete user
    int deleteImage(const uint64_t image_id);

    void update_elo();
};

#endif // IMAGEDAO_HPP
