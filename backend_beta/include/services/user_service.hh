#ifndef USER_SERVICE_HPP
#define USER_SERVICE_HPP

#include "UserDAO.hpp"
#include "User.hpp"

class UserService {
    UserDAO& userDAO;  // Reference to the Data Access Object for users

public:
    UserService(UserDAO& dao);

    // Service operations

    // Standard proceedure to create new account
    bool register_user(const User& user);

    // Admin-only procedure to create new account
    bool create_user(const User& user);

    // Authenticate user through login
    bool login_user(string_view user, string_view password);

    // Get user data
    User get_user(const std::string& userId);
    bool update_user(const User& user);
};

#endif // USER_SERVICE_HPP
