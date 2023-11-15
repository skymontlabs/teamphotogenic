// experiment_dao.hpp
#ifndef EXPERIMENTDAO_HPP
#define EXPERIMENTDAO_HPP

#include "ExperimentModel.hpp"
#include "DatabaseConnector.hpp"
#include <vector>


class experiment_dao
{
    // Handle to the database connection
    database_connection* db_conn_;
    
    // Handle to the Redis cache connector
    redis_connector* rs_conn_;
    
    // Local in-memory cache
    gdsf_cache* lcache_;

    // Bloom filter
    bloom_filter* bloom_;



    // Active (running) experiments
    vector<experiment_model> standard_elos_;

    // Priority users' experiments
    vector<experiment_model> priority_elos_;

    // Active (running) experiments
    vector<experiment_model> standard_elos_;

    // Priority users' experiments
    vector<experiment_model> priority_elos_;


    struct active_exp_value
    {
        uint64_t idx : 62;
        uint64_t type : 1;
        uint64_t priority : 1;
    };

    // Maps to active_exp_ index
    std::unordered_map<uint64_t, active_exp_value> active_map_;


    pool_allocator& pa_;

private:
    inline experiment_model* select_experiment()
    {
        uint32_t std_exp_len = standard_elos_.size();
        uint32_t acv_exp_len = priority_elos_.size();
        uint32_t total_len = std_exp_len + (acv_exp_len << 2);
        uint32_t rn = rand() % total_len;

        return (rn < std_exp_len) ?
                &standard_elos_[rn] :
                &priority_elos_[(rn - acv_exp_len) >> 2];
    }

    // Get experiment in local cache

    int64_t get_exp_active(uint8_t* out, const uint64_t image_id)
    {
        auto it = active_map_.find(image_id);
        if (it != active_map_.end()) {
            active_exp_value av = it->second;

            switch ((av.type << 1) | av.priority) {
                case ((ELO << 1) | SPEED::STANDARD):
                    return standard_elos_[av.idx]->serialize(out) - out;
                case ((ELO << 1) | SPEED::PRIORITY):
                    return priority_elos_[av.idx]->serialize(out) - out;
                case ((LIKERT << 1) | SPEED::STANDARD):
                    return standard_likerts_[av.idx]->serialize(out) - out;
                case ((LIKERT << 1) | SPEED::PRIORITY):
                    return priority_likerts_[av.idx]->serialize(out) - out;
            }
        }
        return 0;
    }

    inline int64_t get_exp_local(uint8_t* out, const uint64_t image_id)
    {
        uint8_t* val = lcache_.find(image_id);
        return val ? 0 : (((experiment_model*)val)->serialize(out) - out);
    }

    // Get experiment in Redis cache
    int64_t get_exp_redis(uint8_t* out, const uint64_t experiment_id, cbk_data* cbk)
    {
        rs_conn_->get_copyout_stackless(experiment_id,
        [out, cbk](size_t length)
        {
            pool_allocator* pool = cbk->pool;

            cbk->gwy->send_response(out, length, cbk->wss,
            [](){
                if (cbk->close())
                    pool->free(cbk->wss);
            });

            // free the memory for out after it is over also
            pool->free(out);
            pool->free(cbk);
        },
        [this]()
        {
            /* failure, check database */
            this->get_exp_cassandra(out, experiment_id, cbk);
        });
    }

    int64_t get_exp_cassandra(uint8_t* out, const uint64_t experiment_id, cbk_data* cbk)
    {
        rs_conn_->get_copyout_stackless(experiment_id,
        [out, cbk](size_t length)
        {
            pool_allocator* pool = cbk->pool;

            cbk->gwy->send_response(out, length, cbk->wss,
            [](){
                if (cbk->close()) pool->free(cbk->wss);
            });

            // free the memory for out after it is over also
            pool->free(out);
            pool->free(cbk);
        });
    }
    
    // Set experiment in local cache
    int64_t set_exp_local(const uint64_t experiment_id, const experiment_model* data)
    {
        experiment_model* em = pool.alloc();
        em->reinit(data);
        lcache_.set(experiment_id, em);
    }

    // Set experiment in local cache
    int64_t set_exp_local(const uint64_t experiment_id, const uint8_t* data)
    {
        experiment_model* em = pool.alloc();
        em->reinit(data);
        lcache_.set(experiment_id, em);
    }
    
    // Set experiment in Redis cache
    int64_t set_exp_redis(const uint64_t experiment_id, const uint8_t* data, cbk_data& cbk)
    {
        rs_conn_->set_stackless(experiment_id, data,
        [cbk](size_t length)
        {
            
        });
    }

    // Delete experiment from the redis cache
    int64_t delete_exp_redis(uint8_t* out, const uint64_t image_id, cbk_data& cbk)
    {
        // get first,
        // then expel the image
        rs_conn_->delete_stackless(image_id,
        [out, cbk](size_t length)
        {
            /*ok, sync with cassandra when done*/
            if (unlikely(cbk->has_set1())) {
                // send response
                *out = RESC_OK;
                cbk->gwy->send_response(out, 1, cbk->wss,
                [](){
                    if (cbk->close())
                        pool->free(cbk->wss);
                });
            } else {
                cbk->set1();
            }
        });
    }

    // Add rating for specific image in the active experiments section
    inline int64_t add_elo_active(uint64_t experiment_id, uint32_t win_idx, uint32_t lose_idx, pool_alloc& pa)
    {
        experiment_model* exp = get_exp_active(experiment_id);
        exp->add_elo_pair(win_idx, lose_idx, pa);
    }

    // Add rating for specific image in the cache
    inline int64_t add_likert_active(experiment_model* exp, uint8_t id)
    {
        // 
        exp->add_rating();
    }

public:
    experiment_dao(database_connection& db_conn);

    // Createx experiment
    int64_t create_experiment(uint64_t user_id, uint32_t img_count)
    {
        // db insert

        set_exp_local();

        set_exp_redis();

        set_exp_cassandra();
    }

    // Get all experiments of user
    int64_t read_exps_by_user(uint64_t user_id, uint32_t limit, uint32_t offset)
    {
        // Assuming you have a function to get the Cassandra session
        CassSession* session = getSession(); // Your mechanism to get a session

        // Create a new statement from the prepared object
        CassStatement* statement = cass_prepared_bind(prepared_exp_by_user_);

        // Bind parameters to the statement
        cass_statement_bind_int32(statement, 0, user_id);
        cass_statement_bind_int32(statement, 1, image_id);

        uint8_t* rqd = requests_pool.alloc();

        execute_stmt_callback(statement, db_get_image_callback, rqd);

        return 0;
    }

    // get 8 pairs of images, with each pair in same experiment
    int64_t read_batch_elo_pairs(uint8_t* out)
    {
        for (int i = 0; i < 8; ++i) {
            experiment_model* ex = select_experiment();
            out = ex->get_elo_pair(out);
        }

        return out;
    }


    // Get experiment by id
    int64_t read_exp_by_id(uint64_t experiment_id, uint64_t user_id)
    {
        // check active
        int64_t len = get_exp_active(out, experiment_id, user_id);
        if (len > 0) return len;

        // cached data
        len = get_exp_local(out, experiment_id, user_id);
        if (len > 0) return len;

        // bloom filter checks if present at all
        if (!bloom_.present(experiment_id)) return 0;

        // redis
        get_exp_redis(out, experiment_id, cbk);

        return -1;
    }

    // Modify experiment 
    int64_t update_experiment(const experiment_model& experiment);

    // Delete experiment (user_id=-1 means admin)
    int64_t delete_experiment(int experimentId, uint64_t user_id);

    friend class image_dao;
    friend class rating_dao;
};

#endif // experiment_dao_HPP






// experiment_dao.cpp
#include "experiment_dao.hpp"




// Other methods...




