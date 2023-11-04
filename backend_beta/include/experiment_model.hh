// ExperimentModel.hpp
#ifndef EXPERIMENTMODEL_HPP
#define EXPERIMENTMODEL_HPP

#include <vector>
#include "ImageModel.hpp"

class ExperimentModel {
public:
    ExperimentModel(int id, const std::string& name);

    int getId() const;
    const std::string& getName() const;

    void setId(int id);
    void setName(const std::string& name);

    void addImage(const ImageModel& image);
    const std::vector<ImageModel>& getImages() const;

    // Other experiment-related methods...

private:
    int experiment_id;
    std::string experiment_name;
    std::vector<ImageModel> images; // A vector of ImageModel, which in turn can hold RatingModel
};

#endif // EXPERIMENTMODEL_HPP
