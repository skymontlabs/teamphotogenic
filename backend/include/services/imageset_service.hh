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


#include "experiment_service.hpp"

experiment_service::experiment_service(ExperimentDAO& dao) : experimentDAO(dao) {}

var_string experiment_service::create_experiment(const uint8_t* data, user_data& ud, response_callback wcb)
{
    // Business logic to create a new experiment
    var_string ret;

    // [1 byte] - image ct
    // [1 byte] - thoroughness
    // [1 byte] - name length
    // [1 byte] - filtered age (lower bound)
    // [1 byte] - filtered age (upper bound)
    // [1 byte] - filtered gender 
    uint8_t image_ct   = READ8(data);
    uint8_t lvl        = READ8(data);
    uint8_t name_len   = READ8(data);

    // Additional data
    if (ud.premium) {
        uint8_t age_lo = READ8(data);
        uint8_t age_hi = READ8(data);
        uint8_t gndr   = READ8(data);

        // Validate image ct
        if (image_ct > 100) {
            ret.assign(100, 1);
            return ret;
        }

        // Validate thoroughness
        if (lvl > 32) {
            ret.assign(101, 1);
            return ret;
        }

        // Validate age
        if (age_lo < 18 || age_hi > 100) {
            ret.assign(102, 1);
            return ret;
        }

        // Validate gender
        if (gndr > 2) {
            ret.assign(103, 1);
            return ret;
        }
    } else {
        if (image_ct > 50) {
            ret.assign(100, 1);
            return ret;
        }
    }

    // this is because reliability is paramount
    // must be acid
    tq_.add([]() {
        // If the filenames are incorrect, return incorrect
        if (idao_.verify(data, image_ct)) {
            return 0;
        }

        // Create experiment
        /// creates experiment
        edao_.create_exp(image_ct, image_list, wcb);
        
        // Insert image
        /// verify images exist
        idao_.insert_images(image_list);
    });

    return var_string;
}

// Modify experiment
var_string experiment_service::read_experiment(const uint8_t* data, user_data& ud, response_callback wcb)
{
    // Business logic to get details of an experiment
    // [8 byte] - experiment id
    uint64_t experiment_id = READ64(data);
    uint8_t* out = pa_.alloc(1024);
    uint64_t user_id = (ud.permissions < PERMISSIONS::MODERATOR) ? ud.user_id : -1;

    // Read experiment
    return edao_.read_exp_by_id(out, experiment_id, user_id, wcb);
}

// Retrieve experiment data
var_string experiment_service::read_all_experiments_by_user(const uint8_t* data, user_data& ud, response_callback wcb)
{
    // Business logic to get details of an experiment
    // [8 byte] - experiment id
    uint64_t user_id = READ64(data);
    uint32_t limit = READ32(data);
    uint32_t offset = READ32(data);

    user_id = (ud.permissions < PERMISSIONS::MODERATOR) ? ud.user_id : user_id;

    // Read experiment
    return edao_.read_exps_by_user(out, limit, offset, user_id, wcb);
}

// Change experiment
var_string experiment_service::update_experiment(const uint8_t* data, user_data& ud, response_callback wcb)
{
    // Name is only thing you can change
    uint8_t option = READ64(data);

    switch (option) {
        case 1: edao_.pause_exp(user_id); break;
        case 2: edao_.pause_exp(user_id); break;
        case 3: edao_.pause_exp(user_id); break;
    }

    // Business logic to retrieve all experiments for a user
}
    
// Delete experiment data
var_string experiment_service::delete_experiment(const uint8_t* data, user_data& ud, response_callback wcb)
{
    uint8_t* out = pa_.alloc(1024);

    edao_.delete_experiment(out, experiment_id, user_id, wcb);
}
    
// Delete all experiments by user
var_string experiment_service::delete_experiments_by_user(const uint8_t* data, user_data& ud, response_callback wcb)
{
    uint8_t* out = pa_.alloc(1024);

    edao_.delete_experiment(out, experiment_id, user_id, wcb);
}



// Other experiment-related method implementations would go here
