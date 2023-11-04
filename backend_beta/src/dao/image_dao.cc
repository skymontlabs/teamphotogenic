
// For functions that could depend upon futures,
//  - Return 0 upon failure (not found or no permissions), won't have callback
//  - Return 1 upon wait, will have callback

//typedef void (*query_callback)(const CassResult* result, CassError code, void* data);

image_model* db_get_image_callback(const CassResult* result, CassError code, void* data)
{

    // If retrieved from the database, add to both caches
    if (dbImage.has_value()) {
        cacheImageLocally(image_id, dbImage.value());
        cacheImageInRedis(image_id, dbImage.value());
    }

    return dbImage;
}


image_model* image_dao::get_image_by_id(const uint64_t image_id) {
    // First, check if the image is in the local cache
    auto lc_image = localCache.find(image_id);
    if (lc_image) {
        return lc_image;
    }

    // If not in bloom filter, file does not exist
    if (!bpresent_.find(image_id)) {
        return ;
    }

    // Next, check if the image is in the Redis cache
    auto redisCachedImage = get_redis_cached_image(image_id);
    if (redisCachedImage.has_value()) {
        // Cache the item locally before returning
        cacheImageLocally(image_id, redisCachedImage.value());
        return redisCachedImage.value();
    }

    // If not in any cache, retrieve from the database
    uint8_t* dbImage = 
}

image_model* image_dao::get_cached_image(const uint64_t image_id) {
    // Implement the logic to get data from Redis cache
    // ...

    // This should return a std::optional<image_model> based on Redis cache hit or miss
    uint8_t* res = redis_.get('GET ', );
}

image_model* image_dao::get_redis_cached_image(const uint64_t image_id) {
    // Implement the logic to get data from Redis cache
    // ...

    // This should return a std::optional<image_model> based on Redis cache hit or miss
    uint8_t* res = redis_.get('GET ', );
}

void image_dao::cacheImageLocally(const uint64_t image_id, const image_model& image)
{
    local_cache.insert(image_id, image);
}

void image_dao::cacheImageInRedis(const uint64_t image_id, const image_model& image) {
    // Implement the logic to set data in Redis cache
    // ...
    uint8_t* res = redis_.get('SET ', );
}

void image_dao::db_get_image() {
    char query[] = "";
    executeQuery(query, query_len, db_get_image_callback, callback_data);
}

