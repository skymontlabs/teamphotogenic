#pragma once

#include <stdio.h>
#include <string>
#include <curl/curl.h>

class curler
{
    int do_curl(std::string_view url, std::string_view body, int type);
    
    
public:
    
    curler()
    {
        curl_global_init(CURL_GLOBAL_ALL);
    }
    
    ~curler()
    {
        curl_global_cleanup();
    }
    
    int send_text(std::string_view number, std::string_view arg, int type)
    {
        /*
        curl -X POST https://api.twilio.com/2010-04-01/Accounts/AC4655f5c85da10d50a4ee3a8e8d51e962/Messages.json \

        -u
        */
        //type
        std::string a = "Body=";
        
        switch (type) {
            case 0:
                a += "ImagesPro: Your password reset link is here: ";
                a += arg;
                a += ". Remember, if you didn't request a reset, don't click on this.";
                break;
            case 1:
                a += "ImagesPro: Your task has finished with";
                a += arg;
                a += " votes.";
                break;
            case 2:
                a += "ImagesPro: Your image has finished with";
                a += arg;
                a += " votes.";
                break;
        }
        
        a += "From=+12088261034";
        a += "To=";
        a += number;
        
        do_curl("https://api.twilio.com/2010-04-01/Accounts/AC4655f5c85da10d50a4ee3a8e8d51e962/Messages.json", a, 0);
        
        return 0;
    }
    
    int send_email(std::string_view email, std::string_view arg, int type)
    {
        std::string a{"{\"From\": \"noreply@imagespro.com\",\"To\": \""};
        a += email;
        a += "\",";
        a += "\"Subject\": \"Task finished\"";
        a += "\"TextBody\": \"Hello dear Postmark user.\",";
        a += "\"MessageStream\": \"outbound\" }";
        
        switch (type) {
            case 0:
                a += "ImagesPro: Your password reset link is here: ";
                a += arg;
                a += ". Remember, if you didn't request a reset, don't click on this.";
                break;
            case 1:
                a += "ImagesPro: Your task has finished with";
                a += arg;
                a += " votes.";
                break;
            case 2:
                a += "ImagesPro: Your image has finished with";
                a += arg;
                a += " votes.";
                break;
        }
        
        return do_curl("https://api.postmarkapp.com/email", a, 1);

    }
};
