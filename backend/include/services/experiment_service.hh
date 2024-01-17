#ifndef EXPERIMENT_SERVICE_HPP
#define EXPERIMENT_SERVICE_HPP

#include "ExperimentDAO.hpp"
#include "Experiment.hpp"
#include <functional>
#include <vector>

typedef std::function<void(const uint8_t*, uint32_t)> response_callback;

class experiment_service
{
    experiment_dao& edao_;
public:
    experiment_service(experiment_dao& dao);

    // Creates new experiment
    var_string create_experiment(const uint8_t* data, user_data& ud, response_callback wcb);

    // Modify experiment
    var_string read_experiment(const uint8_t* data, user_data& ud, response_callback wcb);

    // Retrieve experiment data
    var_string read_all_experiments_by_user(const uint8_t* data, user_data& ud, response_callback wcb);

    // Change experiment
    var_string update_experiment(const uint8_t* data, user_data& ud, response_callback wcb);
    
    // Delete experiment data
    var_string delete_experiment(const uint8_t* data, user_data& ud, response_callback wcb);
    
    // Delete all experiments by user
    var_string delete_experiments_by_user(const uint8_t* data, user_data& ud, response_callback wcb);
};

#endif // EXPERIMENT_SERVICE_HPP
