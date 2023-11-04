#ifndef IMAGEDAO_HPP
#define IMAGEDAO_HPP

#include <unordered_map>
#include <optional>
#include <string>
#include <vector>

class image_dao
{
    DatabaseConnection* dbConnection; // Handle to the database connection
    CacheConnector* cacheConnector; // Handle to the Redis cache connector
    gdsf_cache* local_cache; // Local in-memory cache

    image_model* get_img_locally(const uint64_t image_id);
    image_model* get_img_redis(const uint64_t image_id);
    
    void cache_img_locally(const uint64_t image_id, const image_model& image);
    void cache_img_redis(const uint64_t image_id, const image_model& image);
    // Other cache-related methods...

public:
    image_dao(DatabaseConnection* dbConnection, CacheConnector* cacheConnector);
    ~image_dao();

    image_model getImageById(const std::string& image_id);
    vector<image_model> getImagesByUserId(const std::string& userId);

    int deleteImage(const uint64_t image_id);
};

#endif // IMAGEDAO_HPP
