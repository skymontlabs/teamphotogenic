enum RESPONSES {
    create_user     = 0x01,
    register_user,
    get_seed,
    submit_password,
    submit_code,
    submit_totp,
    read_user,
    read_users,
    update_user,
    delete_user,
    start_session,
    logout,
    read_notifications,
    remove_notification_id,
    reset_password,

    update_preferences,
    read_singular_img,
    read_paired_img,
    upload_image,
    read_image,
    delete_image,
    report_image,
    report_comment,
    read_likerts,
    delete_likert,
    read_elos,
    delete_elo,

    create_experiment,
    read_experiment,
    read_experiment_nm,
    read_experiments,
    update_experiment,
    delete_experiment,


    create_ticket,
    read_ticket,
    read_tickets,
    create_message,
    close_ticket,

    maintenance_mode
}

// USER COMMANDS

void create_user() {
    db_insert_new_user({}, [](){
        send();
    });
}

void register_user() {

}

void get_seed() {


}

void submit_password(uint8_t token[24], uint8_t password[64])
{
    auto usrdata = pwd_.find();

    if (usrdata) {
        // hash password

        // compare password
        if (memcmp() == 0) {
            // return token
        } else {
            // return no token
        }
    }
}

void submit_code(uint8_t random_id[32], uint32_t keycode) {
    auto it = codes_.find(random_id, 32);

    if (it != codes_.end()) {
        if (*it == keycode) {
            uint8_t cookie[32];

            store_cookie();

            send_response(cookie);
        }
    }

    return;
}

void submit_totp(uint8_t random_id[32], uint32_t totp) {
    auto it = codes_.find(random_id, 32);

    // same as above

}

void read_user(uint64_t userid) {
    auto it = users_.find(userid);

    if (it) {
        uint8_t buffer[64];
        size_t len = it->serialize(buffer);

        send(buffer, len, [](){

        });

        return;
    }

    return;
}

void read_users(uint64_t count, uint64_t offset)
{
    if (users_idxlist_.check(offset, offset + count)) {

    }

    else {

    }
}

void change_password_NEW(uint64_t userid)
{
    uint8_t new_seed[16];

    char seed[96] = "CALL PROCEDURE CSEED(";
    memcpy();

}

void update_user(char* email, char* phone, uint32_t credits, uint32_t status, uint8_t password[64])
{
  auto user = users_.find(userid);

  char out[512] = "UPDATE USERS SET ";

  if (user) {
    if (email) {
        "EMAIL=";
    }

    if (phone) {
        "EMAIL=";
    }

    if (credits & 0x80) {
        "EMAIL=";
    }

    if (status & 0x80) {

    }

    if (password) {

    }

    // show me users in X category, must be subscription level
  }
}


void delete_user(uint64_t userid)
{
    if (userid > max_user_current_) {
        return -1;
    }

    auto it = users_.find(userid);

    if (it) {
        // purge from cache

        // purge from 

    } else {
        // does not exist
        return;
    }


    it = itoh(it, userid);
    mys_.call_procedure_str(req, );
}


void logout(uint8_t token[32])
{
    auto tk = tokendata_.find(token);

    if (tk) {
        auto userid = tk->userid;
        current->userid.
        tk->sessions.push_back(current);
    }
}

void read_notifications(uint64_t userid)
{
    auto usr = users_.find(userid);

    if (usr) {
        respond(usr->notifications.serialize());
    } else {
        mys_.call_procedure_cbk(req, "GNOF", , 8,
        [](){

        });
    }
}

void remove_notification_id() {

}

void reset_password(uint8_t password[16], uint8_t seed[16], uint8_t salt[16])
{
    uint8_t password_hash[96];
    char hexify[96];

    //argon2i_hash_raw(t_cost, m_cost, parallelism, pwd, pwdlen, salt, SALTLEN, hash1, HASHLEN);
    argon2d_hash_raw(4, 1<<16, parallelism, pwd, 64, salt, 16, password_hash, 64);

    memcpy(password_hash + 64, seed, 16);
    memcpy(password_hash + 80, salt, 16);

    mys_.call_procedure_str(req, "RPSS", hexify);
}

void read_singular_img(uint64_t imageset_id, uint16_t image_idx)
{
    auto ims = imagesets_.find(imageset_id);
    if (ims) {
        if (ims.check_idx(image_idx)) {

        } else {

        }
    }
}

void read_paired_img() {

}

void upload_image() {

}

void read_image() {

}

delete_image
report_image
report_comment
read_likerts
delete_likert
read_elos
delete_elo

EXPERIMENT COMMANDS
create_experiment
read_experiment
read_experiment_nm
read_experiments
update_experiment
delete_experiment


ADMIN ONLY COMMANDS
create_ticket
read_ticket
read_tickets
create_message
close_ticket

maintenance_mode
