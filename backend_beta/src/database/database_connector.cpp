#include "DatabaseConnector.hpp"
#include <iostream>

DatabaseConnector::DatabaseConnector(const std::string& nodes)
    : cluster_(nullptr), session_(nullptr), nodes_(nodes) {
    cass_log_set_level(CASS_LOG_INFO);
    setupCluster();
    session_ = cass_session_new();
}

DatabaseConnector::~DatabaseConnector() {
    close();
    if (session_) cass_session_free(session_);
    if (cluster_) cass_cluster_free(cluster_);
}

void DatabaseConnector::setupCluster() {
    cluster_ = cass_cluster_new();
    cass_cluster_set_contact_points(cluster_, nodes_.c_str());
    // Additional configuration setup such as authentication, SSL, etc.
}

bool DatabaseConnector::connect() {
    CassFuture* connect_future = cass_session_connect(session_, cluster_);

    if (cass_future_error_code(connect_future) == CASS_OK) {
        cass_future_free(connect_future);
        return true;
    } else {
        handleErrors(connect_future);
        cass_future_free(connect_future);
        return false;
    }
}

void DatabaseConnector::close() {
    if (session_) {
        CassFuture* close_future = cass_session_close(session_);
        cass_future_wait(close_future);
        cass_future_free(close_future);
    }
}

bool DatabaseConnector::execute(const std::string& query) {
    CassStatement* statement = cass_statement_new(query.c_str(), 0);
    CassFuture* result_future = cass_session_execute(session_, statement);

    bool success = cass_future_error_code(result_future) == CASS_OK;
    if (!success) {
        handleErrors(result_future);
    }

    cass_statement_free(statement);
    cass_future_free(result_future);
    return success;
}

CassFuture* DatabaseConnector::executeAsync(const std::string& query) {
    CassStatement* statement = cass_statement_new(query.c_str(), 0);
    CassFuture* result_future = cass_session_execute(session_, statement);
    cass_statement_free(statement);
    return result_future; // The caller needs to handle the future's lifecycle
}


// Asynchronous query execution with callback
void execute_async_with_callback(CassSession* session, const std::string& query) {
    CassStatement* statement = cass_statement_new(query.c_str(), 0);
    CassFuture* future = cass_session_execute(session, statement);

    // Set the callback function to be called when the query execution is complete
    cass_future_set_callback(future, on_query_result, nullptr /* data can be passed here */);

    // The future does not need to be freed here since it will be freed in the callback
    cass_statement_free(statement);
}

void DatabaseConnector::execute_stmt_callback(CassStatement* statement, QueryResultCallback callback, void* callback_data) {
    CassStatement* statement = cass_statement_new(query.c_str(), 0);
    CassFuture* future = cass_session_execute(session_, statement); // Assume session_ is a member variable

    // C-style callback setup
    cass_future_set_callback(future, [](CassFuture* future, void* data) {
        // Unpack the user data
        struct CallbackData {
            QueryResultCallback callback;
            void* data;
        };

        CallbackData* cb_data = static_cast<CallbackData*>(data);
        CassError code = cass_future_error_code(future);
        const CassResult* result = code == CASS_OK ? cass_future_get_result(future) : nullptr;

        // Call the C-style callback function with the result and user data
        cb_data->callback(result, code, cb_data->data);

        if (result) {
            cass_result_free(result);
        }

        // Clean up
        cass_statement_free(statement);
        cass_future_free(future);
        delete cb_data; // Clean up the heap-allocated user data
    }, new CallbackData{callback, callback_data}); // Heap-allocate a structure to pass both callback and user data

    // Do not free statement or future here, as that will happen in the callback
}



void DatabaseConnector::handleErrors(CassFuture* future) {
    const char* message;
    size_t message_length;
    cass_future_error_message(future, &message, &message_length);
    std::cerr << "Error: " << std::string(message, message_length) << std::endl;
    // Log or throw an exception depending on your error handling strategy
}



