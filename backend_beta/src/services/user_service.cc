#include "UserService.hpp"

UserService::UserService(UserDAO& dao) : userDAO(dao) {}

bool UserService::registerUser(const User& user) {
    // Logic for registering a user, which could include validation, encryption of passwords, etc.
    return udao.createUser(user);
}

bool UserService::authenticateUser(const std::string& email, const std::string& password) {
    // Logic to authenticate the user
    User foundUser = udao.getUserByEmail(email);
    // Here you would compare the password after hashing it with the stored hash
    // This is just a placeholder for the logic
    return foundUser.isValid() && foundUser.getPassword() == password;
}

User UserService::getUserDetails(const std::string& userId) {
    // Logic to get user details
    return userDAO.getUserById(userId);
}

bool UserService::updateUserDetails(const User& user) {
    // Logic to update user details
    return userDAO.updateUser(user);
}
