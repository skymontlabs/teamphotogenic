#ifndef USER_SERVICE_HPP
#define USER_SERVICE_HPP

#include "user_dao.hh"
#include "user_model.hh"

class user_service
{
    struct password
    {
        uint8_t data[64];

        bool compare(const uint8_t* other)
        {
            return memcmp(data, other, 64) == 0;
        }
    };

    struct auth_code_data
    {
        user_data ud;
        uint32_t code;
        uint32_t totp;
    };

    struct auth_pw_data
    {
        user_data ud;
        password pw;
        uint32_t totp;
    };

    pool_allocator pa_;

    user_dao& udao_;  // Reference to the Data Access Object for users

    fifo_cache<string, int> codes_;
    fifo_cache<string, totp_key> totp_;
    fifo_cache<string, password_t> login_cache_;

public:
    user_service(user_dao& dao);

    // #1: Admin-only procedure to create new account
    var_string create_user(const uint8_t* in, user_data ud, response_callback wcb);

    // #2: Standard proceedure to create new account
    var_string register_user(const uint8_t* in, uint32_t total_len);

    // #3: Read seed for given username
    var_string read_seed(const uint8_t* in, response_callback wcb);

    // #4: Authenticate user through password
    var_string submit_password(const uint8_t* in);

    // #5: Authenticate user through one-time text/email code
    var_string submit_code(const uint8_t* in, response_callback wcb);

    // #6: Authenticate user through one-time TOTP code
    var_string submit_totp(const uint8_t* in, response_callback wcb);

    // #7: Read user with given ID
    var_string read_user(const uint8_t* in, user_data ud, response_callback wcb);

    // #8: Read users
    var_string read_users(const uint8_t* in, user_data ud, response_callback wcb);

    // #9: Update user with given ID
    var_string update_user(const uint8_t* in, user_data ud, response_callback wcb);

    // #10: Delete self user
    var_string delete_user(const uint8_t* in, user_data ud, response_callback wcb);
    
    // #11: Delete user with given ID (admin only)
    var_string delete_user(const uint8_t* in, user_data ud, response_callback wcb);

    // #12: Read notifications
    var_string read_notifications(const uint8_t* in, user_data ud, response_callback wcb);

    // #13: Create Reset Password Link
    var_string create_reset(const uint8_t* in, response_callback wcb);

    // #14: Reset Password
    var_string reset_password(const uint8_t* in, response_callback wcb);

    // #15: Logout
    var_string logout(const uint8_t* in, user_data ud, response_callback wcb);
};


#include "UserService.hpp"

UserService::UserService(UserDAO& dao) : userDAO(dao) {}



// #1: Admin-only procedure to create new account
var_string user_service::create_user(const uint8_t* in, user_data ud, response_callback wcb)
{
    uint8_t type = READ8(in);
    uint8_t len = READ8(in);
    uint8_t username_len = READ8(in);

    uint8_t* username_data = in;
    in += username_len;
    
    uint8_t* pword = in;

    return (total_len == 3 + 64 + username_len) ?
    udao_.create_user(type, username, pword, wcb) :
    var_string(RESPONSE_CODE::BAD_REQUEST, 1);
}

// #2: Standard proceedure to create new account
var_string user_service::register_user(const uint8_t* in, uint32_t total_len)
{
    //
    uint8_t type = READ8(in);
    uint8_t username_len = READ8(in);

    uint8_t* username_data = in;
    in += username_len;
    
    uint8_t* pword = in;

    return (total_len == 3 + 64 + username_len) ?
    udao_.register_user(type, username, pword, wcb) :
    var_string(RESPONSE_CODE::BAD_REQUEST, 1);
}

    // #3: Read seed for given username
var_string user_service::read_seed(const uint8_t* in, response_callback wcb)
{
    uint8_t type = READ8(in);
    uint8_t len = READ8(in);

    return udao_.read_seed(type, len, username, wcb);
}

// Authenticate user through login
// len must be 8 + 64 = 64
var_string user_service::submit_password(const uint8_t* in)
{
    uint64_t user_code = READ64(in);
    uint8_t* pword = in;

    auto it = login_cache_.find(user_code);
    if (unlikely(it->invalid())) {
        return var_string();
    }

    auth_cache_data acd = it->second;

    if (likely(acd.password.compare(pword))) {
        return (likely(!acd.totp)) ?
        var_string(acd.user_id, 8) :
        var_string(RESPONSE_CODE::FURTHER, 1);
    }

    // incorrect password
    return var_string();
}

var_string user_service::submit_code(const uint8_t* in, response_callback wcb)
{
    uint64_t user_code = READ64(in);
    uint32_t auth_code = READ32(in);

    auto it = login_cache_.find(user_code);
    if (unlikely(it->invalid())) {
        return var_string();
    }

    auth_cache_data acd = it->second;
    if (likely(acd.password.compare(auth_code))) {
        // If not TOTP used, then respond with user id
        return (likely(!acd.totp)) ?
        var_string(acd.user_id, 8) :
        var_string(RESPONSE_CODE::FURTHER, 1);
    }

    // incorrect password
    return var_string();
}

var_string user_service::submit_totp(const uint8_t* in, response_callback wcb)
{
    uint64_t key = READ64(in);
    uint32_t totp_submission = READ32(in);

    totp_key* tk = totp_.find(key);
    if (!tk) {

    }

    if (tk->generate_code(time(NULL), totp_submission)) {
        // correct code, now login
    }
}

// Get user data
var_string user_service::read_user(const uint8_t* in, user_data ud, response_callback wcb)
{
    uint64_t user_id = READ64(in);

    udao_.read_user(user_id);
}

// Get user data
var_string user_service::read_users(const uint8_t* in, user_data ud, response_callback wcb)
{
    uint64_t limit   = READ64(in);
    uint64_t offset  = READ64(in);

    udao_.read_users(limit, offset);
}

// update user
var_string user_service::update_user(const uint8_t* in, user_data ud, response_callback wcb)
{
    // preferences are always separated from own settings/demographics
    uint8_t type     = READ8(data);
    uint8_t age_grp  = READ8(data);
    uint8_t gndr     = READ8(data);
    uint8_t habit    = READ8(data);

    user_model umod;
    umod.set_self();
    umod.set_pref(type, age_grp, gndr, habit);

    udao_.update_user(umod);
}

// Delete user
var_string user_service::delete_user(const uint8_t* in, user_data ud, response_callback wcb)
{
    uint64_t user_id = READ64(in);

    udao_.delete_user(user_id);
}

// Delete user with user id (admin only)
var_string user_service::delete_user(const uint8_t* in, user_data ud, response_callback wcb)
{
    uint8_t* pwd = in;

    udao_.delete_user(ud.user_id, in);
}

// update user
var_string user_service::read_notifications(const uint8_t* in, user_data ud, response_callback wcb)
{
    uint64_t limit = READ64(in);
    uint64_t offset = READ64(in);

    udao_.read_notifications(limit, offset);
}

// create_reset
var_string user_service::create_reset(const uint8_t* in, response_callback wcb)
{
    // create_reset
    uint8_t len = READ8(in);
    uint8_t* username = in;

    udao_.create_reset(username, len);
}

// reset_password
var_string user_service::reset_password(const uint8_t* in, response_callback wcb)
{
    // reset_password
    uint64_t reset_code = READ64(in);
    uint8_t* new_pw = in;

    udao_.reset_password(reset_code, new_pw);
}

// logout
var_string user_service::logout(const uint8_t* in, user_data ud, response_callback wcb)
{
    udao_.logout(ud.user_id);
}


#endif // USER_SERVICE_HPP
