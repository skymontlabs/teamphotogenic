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

    imc_socket pub_;

    bool hasPermission(const user_data& user, const uint64_t requiredPermission);
public:
    image_service(image_dao& idao):
    pub_(std::getenv("IMAGE_SERVER_IP"), std::getenv("IMAGE_SERVER_PORT")) {}

    ~image_service();

    var_string upload_images()
    {
        uint8_t* data = alloc(32);
        uint8_t* p = data;

        WRITE8(p, RESPONSE_CODE::OK)
        WRITE32(p, 16)
        rand(p, 16);

        pub_.send(asio::buffer(data + 4, 5 + 16),[data](){
            cbk(); // send to user
        });
    }

    var_string read_batch_elo_pairs()
    {
        read_batch_elo_pairs();
    }

    var_string read_image(const uint64_t image_id, const uint64_t user_id);
    var_string read_images_by_user(const uint64_t user_id);
    var_string update_image(const uint64_t user_id);
};

#endif // IMAGESERVICE_HPP

#include "ImageService.hpp"
#include "image_dao.hh"
#include "UserModel.hpp"
#include "Logger.hpp"

// Constructor with initialization of members
ImageService::ImageService()
{
    // Initialization of DAOs and connectors would go here
}

// Function to upload an image, including user data for authorization
int ImageService::uploadImage(const image_model& image, const UserData& user) {
    if (!hasPermission(user, "upload")) {
        Logger::log("User does not have permission to upload images.");
        return false;
    }

    // Here you would have logic to actually store the image, such as:
    // - Validate the image (type, size constraints, etc.)
    // - Check if the user has space/quota for the image
    // - Store the image to a persistent storage (like a database or filesystem)
    // - Update any necessary caches

    bool storedSuccessfully = image_dao::storeImage(image);
    return storedSuccessfully;
}

// Function to retrieve an image, given an image ID
image_model* ImageService::getImage(const uint64_t image_id, const UserData& user) {
    // Fetch the image from the database or cache
    image_model* image = image_dao::fetchImage(image_id);

    // Assuming there's some permission to check if a user can view an image
    if (image. || user.expanded_permissions()) {
        Logger::log("User does not have permission to view images.");
        throw std::runtime_error("Unauthorized access.");
    }

    return image;
}

// Function to delete an image, including user data for authorization
int ImageService::deleteImage(const uint64_t image_id, const UserData& user) {
    if (!hasPermission(user, "delete")) {
        Logger::log("User does not have permission to delete images.");
        return false;
    }

    // Here you would have logic to delete the image, such as:
    // - Check if the user is the owner of the image or has delete permissions
    // - Delete the image from persistent storage
    // - Update any necessary caches
    bool deletedSuccessfully = image_dao::deleteImage(image_id);

    return deletedSuccessfully;
}

// Function to update an image's data
bool ImageService::updateImage(const image_model& image, const UserData& user)
{
    // Here you would have logic to update the image, such as:
    // - Validate the new image data
    // - Check if the user is the owner of the image or has edit permissions
    // - Update the image in persistent storage
    // - Update any necessary caches

    bool updatedSuccessfully = image_dao::updateImage(image);

    if (!hasPermission(user, "edit")) {
        Logger::log("User does not have permission to edit images.");
        return false;
    }

    return updatedSuccessfully;
}

// Function to check if the user has the required permissions
bool ImageService::hasPermission(const UserData& user, const uint64_t permissionType) {
    // Permission checking logic would go here
    // For the sake of example, let's just say all users have all permissions
    return true;
}


