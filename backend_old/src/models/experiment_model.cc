// ExperimentModel.cpp
#include "ExperimentModel.hpp"

ExperimentModel::ExperimentModel(int id, const std::string& name)
    : experiment_id(id), experiment_name(name) {}

int ExperimentModel::getId() const {
    return experiment_id;
}

const std::string& ExperimentModel::getName() const {
    return experiment_name;
}

void ExperimentModel::setId(int id) {
    experiment_id = id;
}

void ExperimentModel::setName(const std::string& name) {
    experiment_name = name;
}

void ExperimentModel::addImage(const ImageModel& image) {
    images.push_back(image);
}

const std::vector<ImageModel>& ExperimentModel::getImages() const {
    return images;
}

// Other methods...
