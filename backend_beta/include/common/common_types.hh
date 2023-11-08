// CommonTypes.hpp

#ifndef COMMON_TYPES_HPP
#define COMMON_TYPES_HPP

#include <functional>
#include <cstdint>

// Forward declare the classes to avoid circular dependencies.
// Include the necessary headers where these classes are actually used.
class ws_session;
class pool_allocator;

// Define the response callback type
using response_callback = std::function<void(const uint8_t*, uint32_t)>;

// Struct that holds context information for Cassandra callbacks
struct db_cbk_data
{
    ws_session* wss;
    pool_allocator* pal;

    // Constructor to initialize members
    CassandraCallbackData(ws_session* session, response_callback callback, ImageModel* model):
    wss(session),
    onResponse(callback),
    imageModel(model) {}
};

// Add more common types, enums, constants, etc., as needed.

#endif // COMMON_TYPES_HPP
