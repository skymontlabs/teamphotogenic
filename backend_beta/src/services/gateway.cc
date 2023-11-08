void route_operation(uint8_t* in, ws_session* wss)
{
    msg_type mt = *in++;
    db_cbk_data* cbk = cbk_allocator.alloc();
    *cbk = db_cbk_data(wss, msg_allocator);

    switch (mt) {

        // User authentication and management
        case CreateUser:
            break;
        case UpdateUser:
            break;
        case DeleteUser:
            break;
        case GetUser:
            break;
        case AuthenticateUser:
            break;
        case LoginUser:
            break;


        // User session management
        case UserSessionStart:
        case UserSessionRenew:
        case UserSessionEnd:
            break;


        // Image handling
        case UploadImage:
            img_srv_.upload_images();
            break;

        case UpdateImageDetails:
        case DeleteImage:
        case FetchImage:
        case ListUserImages:
            break;


        // Rating and critique handling
        case SubmitLikertRating:
            rtg_srv_.add_likert(in, cbk);
            break;

        case UpdateRating:
            break;
            
        case DeleteRating:
        case FetchRating:
        case ListImageRatings:
        case SubmitCritique:
        case UpdateCritique:
        case DeleteCritique:
        case FetchCritique:
        case ListImageCritiques:


    }

}