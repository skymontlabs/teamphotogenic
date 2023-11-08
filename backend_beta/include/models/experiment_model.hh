// ExperimentModel.hpp
#ifndef EXPERIMENTMODEL_HPP
#define EXPERIMENTMODEL_HPP

#include <vector>
#include "image_model.hpp"

class ExperimentModel
{
    uint64_t experiment_id;
    char experiment_name[24];

    image_model* images_;
    uint32_t total_images_;
    uint32_t total_ratings_;

public:
    ExperimentModel(int id, const char* name);

    int get_id() const;
    const uint32_t get_name() const;

    void setId(int id);
    void setName(const uint32_t name);

    void addImage(const ImageModel& image);
    const std::vector<ImageModel>& getImages() const;
};

#endif // EXPERIMENTMODEL_HPP
