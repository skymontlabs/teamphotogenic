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
    image_model read_image_by_id(const uint64_t image_id, cbk_data& cbk);

    // #3:
    image_model read_images_by_id(const uint64_t image_id, cbk_data& cbk);

    // #4:
    size_t add_likerts_to_images(likert_model* lm, uint32_t image_ct);

    // #5:
    size_t add_elos_to_images(elo_model* lm, uint32_t image_ct);

    // #6:
    size_t delete_image(const uint64_t image_id, const uint64_t image_id);

    // #7:
    size_t update_elo();
};

#endif // IMAGEDAO_HPP



image_dao::image_dao(database_connection* db_conn, redis_connector* rs_conn):
db_conn_(db_conn),
rs_conn_(rs_conn)
{

}

image_dao::~image_dao()
{

}

struct cbk_data
{
  
};

// For functions that could depend upon futures,
//  - Return 0 upon failure (not found or no permissions), won't have callback
//  - Return 1 upon wait, will have callback

//typedef void (*query_callback)(const CassResult* result, CassError code, void* data);

void* db_get_image_callback(CassFuture* future, void* data)
{
  lock_guard(mutex);

  // If retrieved from the database, add to both caches
  if (dbImage.has_value()) {
    htable_set_image(image_id, dbImage.value());
    cache_set_image(image_id, dbImage.value());
  }

  cbdata._dealloc(data);



  auto cbk_ptr = static_cast<std::function<void(const uint8_t*)>*>(data);

  cbk_ptr(output);

  return NULL;
}


// Callback function that will be called when the statement execution is complete
void on_query_executed(CassFuture* future, void* data)
{
  // Check for execution errors
  if (cass_future_error_code(future) == CASS_OK) {
    printf("Query executed successfully.\n");
    // You can retrieve the result with `cass_future_get_result(future)` if needed
  } else {
    // Handle error
    const char* message;
    size_t message_length;
    cass_future_error_message(future, &message, &message_length);
    fprintf(stderr, "Execute error: %.*s\n", (int)message_length, message);
  }
}

image_model* image_dao::get_image_by_id(const uint64_t image_id, user_data ud)
{
    // First, check if the image is in the local cache
    auto lc_image = lcache_.find(image_id);
    if (lc_image) {
      return lc_image;
    }

    // If not in bloom filter, file does not exist
    if (!bfilt_.contains(image_id)) {
      return FUTURES_FUNCTION_NOT_PRESENT;
    }

    // Next, check if the image is in the Redis cache
    auto redis_img = get_redis_cached_image(image_id);
    if (redis_img.has_value()) {
      // Cache the item locally before returning
      htable_set_image(image_id, redis_img.value());
      return redis_img.value();
    }

    // If not in any cache, retrieve from the database
    return db_get_image_by_user_and_id();
}

image_model* image_dao::cache_set_image(const uint64_t image_id)
{
    // Implement the logic to get data from Redis cache
    // ...

    // This should return a std::optional<image_model> based on Redis cache hit or miss
    uint8_t* res = redis_.get('SET ', );
}

image_model* image_dao::cache_get_image(const uint64_t image_id)
{
    // Implement the logic to get data from Redis cache
    // ...

    // This should return a std::optional<image_model> based on Redis cache hit or miss
    uint8_t* res = redis_.get_with_callback();
}

void image_dao::htable_set_image(const uint64_t image_id, const image_model& image)
{
    local_cache.insert(image_id, image);
}

void image_dao::cacheImageInRedis(const uint64_t image_id, const image_model& image)
{
    // Implement the logic to set data in Redis cache
    // ...
    char query[] = "SET ";
    uint8_t* res = redis_.get(query, it - query);
}

void image_dao::db_get_image(const uint64_t image_id)
{
}

image_model image_dao::findImageByImageId(const uint64_t image_id)
{
}

image_model image_dao::findImagesByExperimentId(const uint64_t image_id)
{
}

int image_dao::db_get_image_by_user_and_id(const uint64_t user_id, const uint64_t image_id)
{
  // Assuming you have a function to get the Cassandra session
  CassSession* session = getSession(); // Your mechanism to get a session

  // Create a new statement from the prepared object
  CassStatement* statement = cass_prepared_bind(prepared_usid_imid_);

  // Bind parameters to the statement
  cass_statement_bind_int32(statement, 0, user_id);
  cass_statement_bind_int32(statement, 1, image_id);

  uint8_t* rqd = requests_pool.alloc();

  execute_stmt_callback(statement, db_get_image_callback, rqd);

  return 0;
}

void execute_prepared_statement_with_callback(CassSession* session, const CassPrepared* prepared, const char* param)
{
}


