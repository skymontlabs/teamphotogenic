#ifndef USERMODEL_HPP
#define USERMODEL_HPP

#include <string>

class user_model
{
    uint64_t id;
    std::string email;
    std::string password;

    uint64_t habits : 3;
    uint64_t age_group : 3;

    uint64_t showme_settings;

public:
    // Constructors
    user_model();
    user_model(const std::string& id, const std::string& username, const std::string& email, const std::string& password);

    // Getter and setter for ID
    std::string getId() const;
    void setId(const std::string& id);

    // Getter and setter for Username
    std::string getUsername() const;
    void setUsername(const std::string& username);

    // Getter and setter for Email
    std::string getEmail() const;
    void setEmail(const std::string& email);

    // Getter and setter for Password
    std::string getPassword() const;
    void setPassword(const std::string& password);
};

#endif // USERMODEL_HPP


// Default Constructor
UserModel::UserModel() : id(""), username(""), email(""), password("") {}

// Parameterized Constructor
UserModel::UserModel(const std::string& id, const std::string& username, const std::string& email, const std::string& password)
    : id(id), username(username), email(email), password(password) {}

// Getters and Setters
std::string UserModel::getId() const { return id; }
void UserModel::setId(const std::string& id) { this->id = id; }

std::string UserModel::getUsername() const { return username; }
void UserModel::setUsername(const std::string& username) { this->username = username; }

std::string UserModel::getEmail() const { return email; }
void UserModel::setEmail(const std::string& email) { this->email = email; }

std::string UserModel::getPassword() const { return password; }
void UserModel::setPassword(const std::string& password) { this->password = password; }

