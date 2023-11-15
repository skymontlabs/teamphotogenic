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

    void set_usr_locally(const uint64_t user_id, const image_model& image);

    void set_usr_redis(const uint64_t user_id, const image_model& image);
    // Other cache-related methods...
    
public:
    user_dao(database_connection* db_conn, redis_connector* rs_conn, gdsf_cache* lcache);

    ~user_dao();

    // Register user
    int32_t register_user(uint8_t* username, uint8_t* password, int type);

    // Create user (admin only)
    int32_t create_user(uint8_t* username, uint8_t* password);

    // Read user
    int32_t read_user(const uint64_t user_id);

    // Read users (admin only)
    int32_t read_users(const uint64_t limit, const uint64_t offset);

    // Update user
    int32_t update_user(const uint64_t user_id);

    // Delete user
    int delete_user(const uint64_t user_id);

    void update_likert_biases();
};

#endif // IMAGEDAO_HPP
