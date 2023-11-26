#ifndef RATINGDAO_HPP
#define RATINGDAO_HPP

#include <optional>
#include <string>
#include <vector>
#include <cassandra.h>
#include "rating_model.hpp"
#include "database_connector.hpp"

class rating_dao
{
    // Handle to the database connection
    database_connection* db_conn_;

    // Bloom filter
    bloom_filter* bloom_;

    // Pool allocator
    pool_allocator pool_;


    
    // Get experiment in local cache
    experiment_model* get_exp_active(const uint64_t experiment_id)
    {
        auto it = active_map_.find(image_id);
        if (it != active_map_.end()) {
            active_exp_value av = it->second;

            switch ((av.type << 1) | av.priority) {
                case ((ELO << 1) | SPEED::STANDARD):
                    return standard_elos_[av.idx];
                case ((ELO << 1) | SPEED::PRIORITY):
                    return priority_elos_[av.idx];
                case ((LIKERT << 1) | SPEED::STANDARD):
                    return standard_likerts_[av.idx];
                case ((LIKERT << 1) | SPEED::PRIORITY):
                    return priority_likerts_[av.idx];
            }
        }

        return NULL;
    }

    // 0. cache rating in server
    void cache_rtg_locally(const uint64_t image_id, const image_model& image);


    // Create elo rating
    CassFuture* ce_;
    // Create likert rating
    CassFuture* cl_;
    // Read elos by image
    CassFuture* re_by_image_;
    // Read likerts by image
    CassFuture* rl_by_image_;
    // Delete likert rating
    CassFuture* dl_;

public:
    // 1. Class is for database only
    rating_dao(database_connection* db_conn);

    // 2. Give elo rating to image
    int64_t create_elo_rating(const elo_model& rating, cbk_data& cbk);

    // 3. Give likert rating to image
    int64_t create_likert_rating(const likert_model& rating, cbk_data& cbk);
    //(uint64_t experiment_id, uint8_t image_idx, uint8_t score, uint32_t tag, const char* comment, uint32_t comment_len)

    // 4. Read ratings for image
    int64_t read_ratings_by_image(uint8_t* out, const uint64_t image_id, cbk_data& cbk);

    // Read rating by user
    int64_t read_ratings_by_user(uint8_t* out, const uint64_t user_id, cbk_data& cbk);

    // Reports comment, but puts whole rating into question
    int64_t report_rating(const uint64_t rating_id, cbk_data& cbk);

    // Deletes rating (admin only behavior)
    int64_t delete_rating(const uint64_t rating_id, cbk_data& cbk);




    experiment_model* get_exp_local(const uint64_t experiment_id)
    {

    }


};

#endif // RATINGDAO_HPP


rating_dao::rating_dao(database_connection* db_conn, redis_connector* rs_conn):
db_conn_(db_conn),
rs_conn_(rs_conn)
{
    // Assuming you have a function to get the Cassandra session
    CassSession* session = getSession(); // Your mechanism to get a session


    //
    ins_ratings = create_prepared_stmt(session, "INSERT INTO ratings (id, image_id, user_id, score, rating_time) VALUES (?, ?, ?, ?, ?)", );


    CassFuture* prep_delete_exp_ = create_prepared_stmt(session, "SELECT * FROM images WHERE image_id=?", );
    CassFuture* prep_delete_exp_ = create_prepared_stmt(session, "SELECT * FROM images WHERE user_id=? AND image_id=?", );
    CassFuture* prep_read_rtg_ = create_prepared_stmt(session, "SELECT * FROM ratings WHERE experiment_id=? AND image_idx=? order by rating_id", );
}

int64_t rating_dao::create_elo_rating(uint64_t experiment_id, uint32_t win_idx, uint32_t lose_idx, pool_alloc& pa)
{
    experiment_model* exp = get_exp_active(experiment_id);
    if (exp) exp->add_elo_pair(win_idx, lose_idx, pa);
}

//(experiment_id, image_idx, score, tag, comment, comment_len);
int64_t rating_dao::create_likert_rating(uint64_t experiment_id, uint8_t image_idx, uint8_t score, uint32_t tag, const char* comment, uint32_t comment_len)
{
    experiment_model* exp = get_exp_active(experiment_id);
    if (exp) exp->add_likert(image_idx, score, tag, comment, comment_len);
}

int64_t rating_dao::read_ratings_by_image(uint8_t* out, uint64_t experiment_id, uint8_t image_idx, cbk_data& cbk)
{
    experiment_model* exp = get_exp_active(experiment_id);
    if (exp) return exp->read_ratings_by_image(out, exp);
    
    exp = get_exp_local(experiment_id);
    if (exp) return exp->read_ratings_by_image(out, exp);

    // database
    cass_statement_bind_int64(ins_ratings, 0, experiment_id);
    cass_statement_bind_int64(ins_ratings, 1, image_idx);

    return 0;
}

int64_t rating_dao::read_ratings_by_user(uint8_t* out, const uint64_t user_id, cbk_data& cbk)
{
    // database
    cass_statement_bind_int64(ins_ratings, 0, experiment_id);
    cass_statement_bind_int64(ins_ratings, 1, image_idx);
}

int64_t rating_dao::report_rating(const uint64_t rating_id, cbk_data& cbk)
{
    experiment_model* exp = get_exp_active(experiment_id);
    if (exp) {
        // also get the rating id (for speed)
        const char* comment = exp->read_rating_by_idx(out, exp);
        reported_ratings_.insert(rating_id, {experiment_id, image_idx, rating_idx, comment});
        return 0;
    } else {
        // check the bloom filter
    }

    return 1;
}

int64_t rating_dao::approve_rating(const uint64_t rating_id, cbk_data& cbk)
{
    auto com = reported_ratings_.find(rating_id);

    if (com) {
        free(it->comment);
        reported_ratings_.remove(it);
    }
}

int64_t rating_dao::disapprove_rating(const uint64_t rating_id, cbk_data& cbk)
{
    auto com = reported_ratings_.find(rating_id);
    if (com) {
        // remove rating from the memory
        experiment_model* exp = get_exp_active(experiment_id);
        // remove rating from the ratings table
        "delete from ratings where experiment_id="
        // remove rating from the experiment
        "update experiment set aggregate_rating=aggregate_rating-" +  + "where experiment_id="
        // remove rating from the image
        "update image set aggregate_rating=aggregate_rating-" +  + "where experiment_id="
    }
}

void rating_dao::insert_ratings(CassSession* session, size_t num_ratings)
{
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


