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

class image_service
{
    image_dao& idao_;

    bool hasPermission(const user_data& user, const uint64_t requiredPermission);
public:
    image_service(image_dao& idao);
    ~image_service();

    image_model* read_image(const uint64_t image_id, const uint64_t user_id);
    vector<image_model> read_images_by_user(const uint64_t user_id);
    bool update_image(const image_model& image, const uint64_t user_id);
};

#endif // IMAGESERVICE_HPP
