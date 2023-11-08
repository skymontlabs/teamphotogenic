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

    // Active (running) experiments
    experiment_model* active_exp_; 



    // Callback after get experiment from DB
    void* db_get_exp_cbk(CassFuture* future, void* data);

    // Callback after modify experiment from DB
    void* db_get_exp_cbk(CassFuture* future, void* data);


    // Get experiment in local cache
    image_model* get_exp_local(const uint64_t image_id);

    // Get experiment in Redis cache
    image_model* get_exp_redis(const uint64_t image_id);
    


    // Set experiment in local cache
    void set_exp_locally(const uint64_t image_id, const image_model& image);
    
    // Set experiment in Redis cache
    void set_exp_redis(const uint64_t image_id, const image_model& image);


public:
    experiment_dao(database_connection& db_conn);

    // Add rating for specific cache
    bool add_rating();

    // Modify experiment 
    bool update_experiment(const experiment_model& experiment);

    // Delete experiment (user_id=-1 means admin)
    bool delete_experiment(int experimentId, uint64_t user_id);

    // Get all experiments of user
    std::vector<ExperimentModel> get_exp_by_user(uint64_t user_id, uint32_t limit, uint32_t offset);

    // Get experiment by user with given id (user_id=-1 means admin)
    ExperimentModel get_exp_by_id(uint64_t experiment_id, uint64_t user_id);


    friend class image_dao;
    friend class rating_dao;
};

#endif // experiment_dao_HPP






// experiment_dao.cpp
#include "experiment_dao.hpp"

experiment_dao::experiment_dao(DatabaseConnector& dbConnector) 
    : dbConnector(dbConnector) {}

bool experiment_dao::saveExperiment(const ExperimentModel& experiment) {
    // Code to save the experiment to the database
}

bool experiment_dao::updateExperiment(const ExperimentModel& experiment) {
    // Code to update the experiment in the database
}

bool experiment_dao::deleteExperiment(int experimentId) {
    // Code to delete the experiment from the database
}

std::vector<ExperimentModel> experiment_dao::read_exp()
{
    // Code to retrieve all experiments from the database
}

ExperimentModel experiment_dao::read_exp(int experiment_id)
{
  // Code to retrieve a single experiment by its ID from the database
}





// Other methods...




