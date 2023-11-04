#ifndef USER_SERVICE_HPP
#define USER_SERVICE_HPP

#include "UserDAO.hpp"
#include "User.hpp"

class UserService {
public:
    UserService(UserDAO& dao);

    // Service operations
    bool registerUser(const User& user);
    bool authenticateUser(const std::string& email, const std::string& password);
    User getUserDetails(const std::string& userId);
    bool updateUserDetails(const User& user);
    // ... other user-related methods ...

private:
    UserDAO& userDAO;  // Reference to the Data Access Object for users
};

#endif // USER_SERVICE_HPP
