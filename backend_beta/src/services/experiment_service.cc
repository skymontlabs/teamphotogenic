#include "ExperimentService.hpp"

ExperimentService::ExperimentService(ExperimentDAO& dao) : experimentDAO(dao) {}

int32_t ExperimentService::create_experiment(const uint8_t* data, response_callback wcb) {
    // Business logic to create a new experiment

    // [1 byte] - image ct
    // [1 byte] - thoroughness
    // [1 byte] - name length
    // [1 byte] - filtered age (lower bound)
    // [1 byte] - filtered age (upper bound)
    // [1 byte] - filtered gender 
    uint8_t image_ct = read8(data);
    uint8_t lvl      = read8(data);
    uint8_t name_len = read8(data);
    uint8_t age_lo   = read8(data);
    uint8_t age_hi   = read8(data);
    uint8_t gndr     = read8(data);

    /// Validate input data

    // Validate image ct
    if (image_ct > 50 && ) return 0;

    // Validate thoroughness
    if (lvl > 32) return 0;

    // Validate age
    if (age_lo < 18 || age_hi > 100) return 0;

    // Validate gender
    if (gndr > 2) return 0;

    // If the filenames are incorrect, return incorrect
    if (idao_.verify(data, image_ct)) {
        return 0;
    }


    // Alert ratings?

    // Save in
    edao_.create_exp(image_ct, image_list, wcb);
    
    idao_.insert_images();

    return
}

// Modify experiment
int32_t experiment_service::read_experiment(const uint8_t* data, user_data& ud, response_callback wcb)
{
    // Business logic to get details of an experiment
    // [8 byte] - experiment id
    uint64_t experiment_id = read64(data);


    // Read experiment
    return edao_.read_exp(experiment_id, user_id);
}

// Retrieve experiment data
int32_t experiment_service::read_all_experiments_by_user(const uint8_t* data, user_data& ud, response_callback wcb)
{
    // Business logic to get details of an experiment
    // [8 byte] - experiment id
    uint32_t limit = read64(data);
    uint32_t offset = read64(data);

    // Read experiment
    return edao_.read_exp(limit, offset, user_id);
}

// Change experiment
int32_t experiment_service::update_experiment(const uint8_t* data, user_data& ud, response_callback wcb)
{
    // Name is only thing you can change
    uint8_t name_len = read64(data);

    // Business logic to retrieve all experiments for a user
    return experimentDAO.getExperimentsByUserId(userId);
}
    
// Delete experiment data
int32_t experiment_service::delete_experiment(const uint8_t* data, user_data& ud, response_callback wcb)
{

}
    
// Delete all experiments by user
int32_t experiment_service::delete_experiments_by_user(const uint8_t* data, user_data& ud, response_callback wcb)
{
    
}



// Other experiment-related method implementations would go here
