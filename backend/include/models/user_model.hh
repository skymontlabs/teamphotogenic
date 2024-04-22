#ifndef USERMODEL_HPP
#define USERMODEL_HPP

#include <string>

class user_model
{
    uint64_t id;
    char email[32];

    uint64_t age_group : 3;
    uint64_t gender : 1;
    uint64_t showme_settings : 3;

public:
    user_model();
};

#endif // USERMODEL_HPP
