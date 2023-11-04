#ifndef EXPERIMENT_SERVICE_HPP
#define EXPERIMENT_SERVICE_HPP

#include "ExperimentDAO.hpp"
#include "Experiment.hpp"
#include <vector>

class ExperimentService {
public:
    ExperimentService(ExperimentDAO& dao);

    bool createExperiment(const Experiment& experiment);
    Experiment getExperimentDetails(const std::string& experimentId);
    std::vector<Experiment> getAllExperimentsForUser(const std::string& userId);
    bool updateExperiment(const Experiment& experiment);
    // Additional methods related to experiments can be added here

private:
    ExperimentDAO& experimentDAO;
};

#endif // EXPERIMENT_SERVICE_HPP
