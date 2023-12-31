#ifndef IMAGEDAO_HPP
#define IMAGEDAO_HPP

#include <unordered_map>
#include <optional>
#include <string>
#include <vector>

class image_dao
{
    // Handle to the database connection
    database_connection* db_conn_;

    // Handle to the Redis cache connector
    redis_connector* rs_conn_;

    // Local in-memory cache
    gdsf_cache* lcache_;

    // Bloom filter
    bloom_filter* bfilt_;

    size_t get_img_locally(const uint64_t image_id);
    size_t get_img_redis(const uint64_t image_id);
    
    void cache_img_locally(const uint64_t image_id, const image_model& image);
    void cache_img_redis(const uint64_t image_id, const image_model& image);
    
public:
    image_dao(database_connection* db_conn, redis_connector* rs_conn);
    ~image_dao();

    // #1: Create image
    size_t create_images(uint64_t experiment_id, uint64_t user_id, uint32_t count)
    {
        "INSERT INTO S() VALUES"
            "()\n"
            "()";

        for (int i = 0; i < count; ++i) {
            append_str(it, , );
        }

        "";
    }

    // #2:
    image_model read_image_by_id(const uint64_t image_id, cbk_data& cbk)
    {

    }

    // #3:
    image_model read_images_by_id(const uint64_t image_id, cbk_data& cbk)
    {

    }

    // #4:
    size_t add_likert_to_image(likert_model& lm)
    {

    }

    // #5:
    size_t add_elo_to_image(elo_model& lm)
    {
    }

    // #6:
    size_t delete_image(const uint64_t image_id, const uint64_t image_id);

    // #7:
    size_t update_elo();
};

#endif // IMAGEDAO_HPP
