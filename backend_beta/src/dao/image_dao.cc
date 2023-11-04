image_dao::image_dao(database_connection* db_conn, redis_connector* rs_conn):
db_conn_(db_conn),
rs_conn_(rs_conn)
{
    // Assuming you have a function to get the Cassandra session
    CassSession* session = getSession(); // Your mechanism to get a session


    //
    CassFuture* prepare_future = cass_session_prepare_n(session, "SELECT * FROM images WHERE experiment_id=?", );
    // 
    cass_future_wait(prepare_future);
    // Check for preparation errors
    prepared_exid = cass_future_get_prepared(prepare_future);
    if (prepared == NULL) {

    }

    CassFuture* prepare_future = cass_session_prepare_n(session, "SELECT * FROM images WHERE image_id=?", );
    cass_future_wait(prepare_future);
    prepared_imid = cass_future_get_prepared(prepare_future);


    CassFuture* prepare_future = cass_session_prepare_n(session, "SELECT * FROM images WHERE user_id=? AND image_id=?", );
    cass_future_wait(prepare_future);
    prepared_usid_imid = cass_future_get_prepared(prepare_future);

}

image_dao::~image_dao()
{

}

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

int main() {
  // Initialize and connect to the cluster and create a session
  CassCluster* cluster = cass_cluster_new();
  CassSession* session = cass_session_new();
  // ... (configure cluster, connect session, etc.) ...

  // Prepare the statement only once
  const char* query = "INSERT INTO my_table (id, value) VALUES (?, ?)";
  CassFuture* prepare_future = cass_session_prepare(session, query);
  cass_future_wait(prepare_future);

  // Check for preparation errors
  const CassPrepared* prepared = cass_future_get_prepared(prepare_future);
  if (prepared == NULL) {
    // Handle error
    const char* message;
    size_t message_length;
    cass_future_error_message(prepare_future, &message, &message_length);
    fprintf(stderr, "Prepare error: %.*s\n", (int)message_length, message);
  } else {
    // Execute the statement with a callback
    execute_prepared_statement_with_callback(session, prepared, "parameter_value");
    // ... You can execute more statements here ...

    // Since we're using async execution, we need to wait for callbacks to complete
    // This could be replaced with a more sophisticated event loop
    sleep(1); // Replace with a proper wait mechanism
  }

  // Clean up
  cass_future_free(prepare_future);
  if (prepared) {
    cass_prepared_free(prepared);
  }
  cass_session_free(session);
  cass_cluster_free(cluster);

  return 0;
}

