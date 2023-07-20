//
//  curler.cpp
//  ImagesPro Site
//
//  Created by Stephen on 12/27/21.
//

#include "curler.hpp"

int curler::do_curl(std::string_view url, std::string_view body, int type)
{
    CURL *curl = curl_easy_init();
    CURLcode res;
    
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.data());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=daniel&project=curl");
        
        if (type == 0) {
            curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
            curl_easy_setopt(curl, CURLOPT_USERPWD, "AC4655f5c85da10d50a4ee3a8e8d51e962:b14e449b05ff931e570142221d63d343");
        } else {
            struct curl_slist *headers = NULL;
            headers = curl_slist_append(headers, "Accept: application/json");
            headers = curl_slist_append(headers, "Content-Type: application/json");
            headers = curl_slist_append(headers, "X-Postmark-Server-Token: 8b03b7ca-dd6f-4954-a335-8f7fa00054dc");
            
            curl_easy_setopt(curl, CURLOPT_HEADER, headers);
        }
        
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, body.length());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.data());

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            return -1;

        curl_easy_cleanup(curl);
    }
    
    return 0;
}
