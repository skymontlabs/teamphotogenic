#ifndef IMAGESERVICE_HPP
#define IMAGESERVICE_HPP

#include <string>
#include <vector>
#include <optional>
#include "ImageDAO.hpp"
#include "ImageModel.hpp"

// Assume we have a user_data struct defined somewhere that contains user-related information
struct user_data {
    uint64_t user_id;
    std::string permissions; // This could also be a permissions struct or bitfield
};

class image_service {
public:
    image_service(ImageDAO& imageDao);
    ~image_service();

    image_model* retrieve_image(const uint64_t imageId, const user_data& user);
    std::vector<ImageModel> retrieve_images_by_user(const uint64_t userId, const user_data& user);
    bool uploadImage(const ImageModel& image, const user_data& user);
    bool updateImage(const ImageModel& image, const user_data& user);
    bool deleteImage(const uint64_t imageId, const user_data& user);

private:
    ImageDAO& imageDao;
    bool hasPermission(const user_data& user, const uint64_t requiredPermission);

};

#endif // IMAGESERVICE_HPP
