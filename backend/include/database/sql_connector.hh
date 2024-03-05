#ifndef DATABASECONNECTOR_HPP
#define DATABASECONNECTOR_HPP

#include <cassandra.h>
#include <string>

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

