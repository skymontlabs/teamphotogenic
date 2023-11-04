#include "ExperimentService.hpp"

ExperimentService::ExperimentService(ExperimentDAO& dao) : experimentDAO(dao) {}

bool ExperimentService::createExperiment(const Experiment& experiment) {
    // Business logic to create a new experiment
    return experimentDAO.createExperiment(experiment);
}

Experiment ExperimentService::getExperimentDetails(const std::string& experimentId) {
    // Business logic to get details of an experiment
    return experimentDAO.getExperimentById(experimentId);
}

std::vector<Experiment> ExperimentService::getAllExperimentsForUser(const std::string& userId) {
    // Business logic to retrieve all experiments for a user
    return experimentDAO.getExperimentsByUserId(userId);
}

bool ExperimentService::updateExperiment(const Experiment& experiment) {
    // Business logic to update an experiment's details
    return experimentDAO.updateExperiment(experiment);
}

// Other experiment-related method implementations would go here
