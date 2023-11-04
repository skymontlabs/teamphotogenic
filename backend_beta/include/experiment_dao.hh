// ExperimentDAO.hpp
#ifndef EXPERIMENTDAO_HPP
#define EXPERIMENTDAO_HPP

#include "ExperimentModel.hpp"
#include "DatabaseConnector.hpp"
#include <vector>

class ExperimentDAO {
public:
    ExperimentDAO(DatabaseConnector& dbConnector);

    bool saveExperiment(const ExperimentModel& experiment);
    bool updateExperiment(const ExperimentModel& experiment);
    bool deleteExperiment(int experimentId);
    std::vector<ExperimentModel> getAllExperiments();
    ExperimentModel getExperimentById(int experimentId);

    // Other methods related to experiment data access...

private:
    DatabaseConnector& dbConnector; // Reference to a database connector
};

#endif // EXPERIMENTDAO_HPP

// ExperimentDAO.cpp
#include "ExperimentDAO.hpp"

ExperimentDAO::ExperimentDAO(DatabaseConnector& dbConnector) 
    : dbConnector(dbConnector) {}

bool ExperimentDAO::saveExperiment(const ExperimentModel& experiment) {
    // Code to save the experiment to the database
}

bool ExperimentDAO::updateExperiment(const ExperimentModel& experiment) {
    // Code to update the experiment in the database
}

bool ExperimentDAO::deleteExperiment(int experimentId) {
    // Code to delete the experiment from the database
}

std::vector<ExperimentModel> ExperimentDAO::getAllExperiments() {
    // Code to retrieve all experiments from the database
}

ExperimentModel ExperimentDAO::getExperimentById(int experimentId) {
    // Code to retrieve a single experiment by its ID from the database
}

// Other methods...
