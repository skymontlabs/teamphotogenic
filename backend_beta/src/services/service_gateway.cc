void service_gateway::route_operation(uint8_t* in, ws_session* wss)
{
    msg_type mt = *in++;
    db_cbk_data* cbk = cbk_allocator.alloc();
    *cbk = db_cbk_data(wss, msg_allocator);

    switch (mt) {

        // User authentication and management
        case CreateUser:
            usr_srv_.create_user(, cbk);
            break;

        case UpdateUser:
            usr_srv_.update_user(, );
            break;

        case DeleteUser:
            usr_srv_.delete_user(, );
            break;

        case GetUser:
            usr_srv_.get_user(, );
            break;

        case AuthenticateUser:
            usr_srv_.auth_user(, );
            break;

        case LoginUser:
            usr_srv_.login_user(, );
            break;


        // User session management
        case UserSessionStart:
        
            break;

        case UserSessionRenew:
        
            break;

        case UserSessionEnd:
            break;


        // Image handling
        case UploadImage:
            img_srv_.upload_images();
            break;

        case UpdateImageDetails:
        
            break;

        case DeleteImage:
            break;
        
        case FetchImage:
            break;

        case ListUserImages:
            break;


        // Rating and critique handling
        case SubmitLikertRating:
            rtg_srv_.add_likert(in, cbk);
            break;

        case UpdateRating:
            break;

        case DeleteRating:
            break;
            
        case FetchRating:
            break;
            
        case ListImageRatings:
            break;


    }

}