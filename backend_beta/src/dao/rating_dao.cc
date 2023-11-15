
image_dao::image_dao(database_connection* db_conn, redis_connector* rs_conn):
db_conn_(db_conn),
rs_conn_(rs_conn)
{
    // Assuming you have a function to get the Cassandra session
    CassSession* session = getSession(); // Your mechanism to get a session


    //
   ins_ratings = create_prepared_stmt(session, "INSERT INTO ratings (id, image_id, user_id, score, rating_time) VALUES (?, ?, ?, ?, ?)", );


    CassFuture* prepare_future = create_prepared_stmt(session, "SELECT * FROM images WHERE image_id=?", );
    
    CassFuture* prepare_future = create_prepared_stmt(session, "SELECT * FROM images WHERE user_id=? AND image_id=?", );

}


#include <cassandra.h>

void insert_ratings(CassSession* session, size_t num_ratings) {
    // Prepare the single INSERT statement
    /*
    const char* query = ;
    CassFuture* prepare_future = cass_session_prepare(session, query);
    cass_future_wait(prepare_future);
    const CassPrepared* prepared = cass_future_get_prepared(prepare_future);
    cass_future_free(prepare_future);

    if (prepared == NULL) {
        // Handle error. For example, you can retrieve the error message with cass_future_error_message()
        return;
    }*/

    for (size_t i = 0; i < num_ratings; ++i) {
        cass_statement_bind_int64(ins_ratings, 0, r->id);
        cass_statement_bind_int64(ins_ratings, 1, r->image_id);
        cass_statement_bind_int64(ins_ratings, 2, r->user_id);
        cass_statement_bind_int8(ins_ratings, 3, r->score);
        cass_statement_bind_int64(ins_ratings, 4, r->rating_time); // Assuming rating_time is a bigint (timestamp)

        execute_stmt_callback(ins_ratings, noop, cbdata);
    }

    // Clean up the prepared statement
    cass_prepared_free(prepared);
}

