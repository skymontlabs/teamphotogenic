#ifndef IMAGESERVICE_HPP
#define IMAGESERVICE_HPP

#include <string>
#include <vector>
#include <optional>
#include "image_dao.hpp"
#include "image_model.hpp"

// Assume we have a user_data struct defined somewhere that contains user-related information
struct user_data {
    uint64_t user_id;
    std::string permissions; // This could also be a permissions struct or bitfield
};

class image_service {
public:
    image_service(image_dao& idao);
    ~image_service();

    image_model* retrieve_image(const uint64_t imageId, const user_data& user);
    std::vector<image_model> retrieve_images_by_user(const uint64_t userId, const user_data& user);
    bool uploadImage(const image_model& image, const user_data& user);
    bool updateImage(const image_model& image, const user_data& user);
    bool deleteImage(const uint64_t imageId, const user_data& user);

private:
    image_dao& idao_;
    bool hasPermission(const user_data& user, const uint64_t requiredPermission);
};

#endif // IMAGESERVICE_HPP
