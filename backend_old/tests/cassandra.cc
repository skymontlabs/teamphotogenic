#ifndef DATABASECONNECTOR_HPP
#define DATABASECONNECTOR_HPP

#include <cassandra.h>
#include <string>
#include <iostream>

typedef void (*query_callback)(const CassResult* result, CassError code, void* data);

class DatabaseConnector {
public:
    DatabaseConnector(const std::string& nodes);
    ~DatabaseConnector();

    bool connect();
    void close();

    // Query execution methods
    bool execute(const std::string& query);
    CassFuture* executeAsync(const std::string& query);

    // More specific methods could be added for parameterized queries or for retrieving data
    // ...

private:
    CassCluster* cluster_;
    CassSession* session_;
    std::string nodes_;

    // Utility methods
    void setupCluster();
    void handleErrors(CassFuture* future);
};

#endif // DATABASECONNECTOR_HPP


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
void execute_query_cbk(CassStatement* statement, QueryResultCallback callback) {
    CassFuture* future = cass_session_execute(session_, statement);

    // Set the callback function to be called when the query execution is complete
    cass_future_set_callback(future, on_query_result, nullptr /* data can be passed here */);

    // The future does not need to be freed here since it will be freed in the callback
    cass_statement_free(statement);
}

// Asynchronous query execution with callback
const CassPrepared* create_prepared_stmt(CassSession* session, const char* query, const size_t length)
{
    // Create future
    CassFuture* prepare_future = cass_session_prepare_n(session, query, length);
    
    // Wait for finish
    cass_future_wait(prepare_future);

    // Check for preparation errors
    return cass_future_get_prepared(prepare_future);
}

void DatabaseConnector::execute_stmt_callback(CassStatement* statement, QueryResultCallback callback, void* callback_data)
{
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

void DatabaseConnector::handleErrors(CassFuture* future)
{
    const char* message;
    size_t message_length;
    cass_future_error_message(future, &message, &message_length);
    std::cerr << "Error: " << std::string(message, message_length) << std::endl;
    // Log or throw an exception depending on your error handling strategy
}






#include <cassandra.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
  /* Setup and connect to cluster */
  CassFuture* connect_future = NULL;
  CassCluster* cluster = cass_cluster_new();
  CassSession* session = cass_session_new();
  char* hosts = "10.12.96.4";
  if (argc > 1) {
    hosts = argv[1];
  }

  /* Add contact points */
  cass_cluster_set_contact_points(cluster, hosts);

  /* Provide the cluster object as configuration to connect the session */
  connect_future = cass_session_connect(session, cluster);

  if (cass_future_error_code(connect_future) == CASS_OK) {
    CassFuture* close_future = NULL;

    /* Build statement and execute query */
    const char* query = "SELECT release_version FROM system.local";
    CassStatement* statement = cass_statement_new(query, 0);

    CassFuture* result_future = cass_session_execute(session, statement);

    if (cass_future_error_code(result_future) == CASS_OK) {
      /* Retrieve result set and get the first row */
      const CassResult* result = cass_future_get_result(result_future);
      const CassRow* row = cass_result_first_row(result);

      if (row) {
        const CassValue* value = cass_row_get_column_by_name(row, "release_version");

        const char* release_version;
        size_t release_version_length;
        cass_value_get_string(value, &release_version, &release_version_length);
        printf("release_version: '%.*s'\n", (int)release_version_length, release_version);
      }

      cass_result_free(result);
    } else {
      /* Handle error */
      const char* message;
      size_t message_length;
      cass_future_error_message(result_future, &message, &message_length);
      fprintf(stderr, "Unable to run query: '%.*s'\n", (int)message_length, message);
    }

    cass_statement_free(statement);
    cass_future_free(result_future);

    /* Close the session */
    close_future = cass_session_close(session);
    cass_future_wait(close_future);
    cass_future_free(close_future);
  } else {
    /* Handle error */
    const char* message;
    size_t message_length;
    cass_future_error_message(connect_future, &message, &message_length);
    fprintf(stderr, "Unable to connect: '%.*s'\n", (int)message_length, message);
  }

  cass_future_free(connect_future);
  cass_cluster_free(cluster);
  cass_session_free(session);

  return 0;
}