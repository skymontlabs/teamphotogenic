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
//using response_callback = std::function<void(const uint8_t*, uint32_t)>;
using std::function<void(const uint8_t*, uint32_t)> response_callback;
using std::function<void(const uint8_t*, uint32_t)> response_callback;

struct var_string
{
    union {
        uint8_t* str_ptr;
        uint8_t str_data[8];
    };

    uint64_t size;

};

// Struct that holds context information for Cassandra callbacks
struct cbk_data
{
    gateway* gwy;
    ws_session* wss;
    pool_allocator* pal;
    query_result qs;
    
    uint8_t* data;

    int msg_type;


    // Constructor to initialize members
    cbk_data(ws_session* session, response_callback callback, ImageModel* model):
    wss(session),
    onResponse(callback),
    imageModel(model) {}
};

// Add more common types, enums, constants, etc., as needed.

#endif // COMMON_TYPES_HPP
