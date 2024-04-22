//RateLimiter rl

// Authentication class
class Authentication {
    std::map<uint64_t, user_data> user_credentials; // Maps user IDs to passwords for simplicity

public:
    Authentication() {
        // Initialize with some user credentials
        user_credentials["user1"] = "password1";
        user_credentials["user2"] = "password2";
        // ... more users ...
    }

    bool authenticate(const ws_session& session) {
        std::string user_id = session.get_user_id();
        // Check if the user ID exists in the credentials map
        auto it = user_credentials.find(user_id);
        if (it != user_credentials.end()) {
            // Here you would normally check the password or other credentials
            // For simplicity, we just return true if the user ID is found
            return true;
        }
        return false;
    }
};

using std::function<void(var_string)> = resp_cbk;



void service_gateway::route_operation(uint8_t* in, ws_session* wss)
{
    var_string ret;

    auto cbk_func = [&wss, &pool_](var_string vs) {
        if (vs.size > 8) {
            wss->send(vs.str_ptr, vs.size, [&pool_]() {
                pool_.deallocate(vs.str_ptr, POW2_ROUND_UP(vs.size));
            });
        } else {
            wss->send(vs.str_data, vs.size, [&pool_]() {

            });
        }
    };

    msg_type mt = *in++;
    //db_cbk_data* cbk = cbk_allocator.alloc();
    //*cbk = db_cbk_data(wss, msg_allocator);

    // check rate limiting
    if (unlikely(rl.grant_access(wss->ip_address()))) {
        // send rate limit
    }



    a<ws_session*, s> auth_tokens;
    a<ws_session*, s> auth;
    a<uint64_t, vector<ws_session*>> user2sessions;


    // check authentication
    user_data ud = auth.authenticate(wss);
    if (ud.user_id == 0) {
        // 
        goto send_end;
    }



    // SOME OF THESE WILL RESULT IN CHANGING THE SOCKET OWNERSHIP

    switch (mt) {
        // User authentication and management
        case msg_type::create_user:
            ret = usr_srv_.create_user(in, ud, cbk_func);
            break;

        case msg_type::update_user:
            ret = usr_srv_.update_user(in, ud, cbk_func);
            break;

        case msg_type::delete_user:
            ret = usr_srv_.delete_user(in, ud, cbk_func);
            break;

        case msg_type::get_user:
            ret = usr_srv_.get_user(in, ud, cbk_func);
            break;

        case msg_type::login:
            // if correct, then insert
            ret = usr_srv_.login(in, ud);
            if (ret.size == sizeof()) {
                auth.insert(wss, ret.str_data);
                ret.assign(RESPONSE_CODE::OK, 1);
            }
            break;

        case msg_type::upload_images:
            img_srv_.upload_images(ud, cbk_func);
            break;




        case msg_type::read_notifications:
            not_srv_.read_notifications();
            break;

        case msg_type::rate_and_read_likerts:
            ret = img_srv_.read_batch_elo_pairs(in, ud);
            ret = rtg_srv_.rate_likerts(in, ud, cbk_func);

            //ret.set(0, CREATED_WITH_BODY);
            merge_both_rets();
            break;

        case msg_type::rate_and_read_elos:
            ret = img_srv_.read_batch_elo_pairs(in, ud);
            ret = rtg_srv_.rate_elos(in, ud, cbk_func);
            merge_both_rets();
            break;

        case msg_type::skip_likerts:
            ret = rtg_srv_.skip_likerts(in, ud, cbk_func);
            break;

        case msg_type::skip_elos:
            ret = rtg_srv_.skip_elos(in, ud, cbk_func);
            break;
        case msg_type::rate_likerts:
            ret = rtg_srv_.rate_likerts(in, ud, cbk_func);
            break;

        case msg_type::rate_elos:
            ret = rtg_srv_.rate_elos(in, ud, cbk_func);
            break;








        case msg_type::read_image:
            ret = img_srv_.read_image(in, ud, cbk_func);
            break;

        case msg_type::delete_image:
            ret = img_srv_.delete_image(in, ud, cbk_func);
            break;

        case msg_type::report_image:
            ret = img_srv_.report_image(in, ud, cbk_func);
            break;

        case msg_type::report_comment:
            ret = img_srv_.report_comment(in, ud, cbk_func);
            break;

        case msg_type::read_likerts:
            ret = rtg_srv_.read_likerts();
            break;

        case msg_type::delete_likert:
            ret = rtg_srv_.read_likerts();
            break;

        case msg_type::read_elos:
            ret = rtg_srv_.read_likerts();
            break;

        case msg_type::delete_elo:
            ret = rtg_srv_.read_likerts();
            break;






        case msg_type::create_experiment:
            ret = exp_srv_.create_experiment(in, ud, cbk_func);
            break;

        case msg_type::read_all_experiments_by_user:
            ret = exp_srv_.read_all_experiments_by_user(in, ud, cbk_func);
            break;
            
        case msg_type::read_experiment:
            ret = exp_srv_.read_experiment(in, ud, cbk_func);
            break;
            
        case msg_type::update_experiment:
            ret = exp_srv_.update_experiment(in, ud, cbk_func);
            break;
            
        case msg_type::delete_experiment:
            ret = exp_srv_.update_experiment(in, ud, cbk_func);
            break;









        case msg_type::create_ticket:
            ret = tkt_srv_.create_ticket(in, ud, cbk_func);
            break;

        case msg_type::read_ticket:
            ret = tkt_srv_.read_ticket(in, ud, cbk_func);
            break;
            
        case msg_type::read_all_tickets_by_user:
            ret = tkt_srv_.read_all_tickets_by_user(in, ud, cbk_func);
            break;
            
        case msg_type::create_message:
            ret = tkt_srv_.create_message(in, ud, cbk_func);
            break;
            
        case msg_type::close_ticket:
            ret = tkt_srv_.close_ticket(in, ud, cbk_func);
            break;




        case msg_type::maintenance_mode:
            break;

    }

send_end:
    if (ret.size > 0) {
        cbk_func(ret);
    } else if (ret.size == 0) {
        // not found
        cbk_func(var_str(RESPONSE_CODE::NOT_FOUND, 1));
    } else {
        // wait for db response
    }



}