#ifndef EXPERIMENT_SERVICE_HPP
#define EXPERIMENT_SERVICE_HPP

#include "ExperimentDAO.hpp"
#include "Experiment.hpp"
#include <functional>
#include <vector>

typedef std::function<void(const uint8_t*, uint32_t)> response_callback;

class ExperimentService
{
    experiment_dao& edao_;
public:
    ExperimentService(experiment_dao& dao);

    // Creates new experiment
    int32_t create_experiment(const uint8_t* data, user_data& ud, response_callback wcb);

    // Modify experiment
    int32_t read_experiment(const uint8_t* data, user_data& ud, response_callback wcb);

    // Retrieve experiment data
    int32_t read_all_experiments_by_user(const uint8_t* data, user_data& ud, response_callback wcb);

    // Change experiment
    int32_t update_experiment(const uint8_t* data, user_data& ud, response_callback wcb);
    
    // Delete experiment data
    int32_t delete_experiment(const uint8_t* data, user_data& ud, response_callback wcb);
    
    // Delete all experiments by user
    int32_t delete_experiments_by_user(const uint8_t* data, user_data& ud, response_callback wcb);
};

#endif // EXPERIMENT_SERVICE_HPP
