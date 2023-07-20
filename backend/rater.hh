#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "util/vector.hh"

struct user
{
    uint64_t user_id : 61;
    uint64_t login : 3; // Google or Facebook or Instagram

    string email;

    uint8_t* ratings;
    uint32_t ratings_cur;
    uint32_t ratings_total;
    uint32_t ratings_avg;

    inline void add_rating(uint8_t id, uint8_t rating, uint32_t user)
    {
        ratings[id * rpi + ratings_cur[id]] = rating;
    }
};

/*
struct image
{
    uint64_t image_id;

    uint64_t task_id;
    uint64_t user_id;
};*/

struct image_set
{
    uint64_t imageset_id;

    uint8_t* users;
    uint8_t* user_means;
    uint8_t* ratings;
    uint32_t* ratings_cur;
    uint32_t ratings_total;

    // uint16_t scores;
    
    // pair<string, int> comments;
    uint64_t user_id;

    image_set(uint32_t ratings_per_image)
    {
        users = new uint32_t[ratings_per_image * image_ct];
        user_means = new uint8_t[ratings_per_image * image_ct];
        ratings = new uint8_t[ratings_per_image * image_ct];
        ratings_cur = new uint32_t[image_ct];
    }

    void add_rating(uint8_t id, uint8_t rating, uint32_t user)
    {
        // make sure image
        if (id > images_ct)
            return -1;

        ratings[id * ratings_per_image + ratings_cur[id]] = (rating);
        users[id * ratings_per_image + ratings_cur[id]] = user;
    }
};

/*
struct rating
{
    uint16_t score : 3;
    uint16_t tags : 13;
    string comment;
};
*/
// map<uint128_t, uint64_t>
void text_user()
{
    /*
    curl -X POST "https://" \
    --data-urlencode "Body=Hi there" \
    --data-urlencode "From=+15017122661" \
    --data-urlencode "To=+15558675310" \
    -u 
    */
    // http://example.com?p1=value%201&p2=value%202

    char data[] = "/2010-04-01/Accounts/$TWILIO_ACCOUNT_SID/Messages.json";
    char* it = &data[];
    memcpy(it, "Body=\"The%20TeamPhotogenic%20image%20set%20uploaded%20on%20", );
    memcpy(it, "<datetime>", );
    memcpy(it, "%20has%20finished%20with%20<x>%20votes.\"", );

    memcpy(it, "&From=+NUMBER", );
    memcpy(it, "&To=+", );
    memcpy(it, other_number, );

    memcpy(it, "<datetime>", );


    c.init("api.twilio.com", data);
    c.auth("$TWILIO_ACCOUNT_SID:$TWILIO_AUTH_TOKEN");

    c.send();
}

int finalize(uint128_t alias_id, uint32_t rating, uint32_t user_id)
{
    // remove this from the 
    rid_decoder.remove(alias_id);
    task_map.remove(real_id);

    // send alert or email
}

void regenerate_alias(tsl::robin_map<uint32_t, uint32_t>::iterator ait)
{
    rid_decoder.erase(ait);
    rid_decoder.insert({alias_id, real_id});
}

int rate_image(uint128_t alias_id, uint32_t rating, uint32_t user_id)
{
    auto dit = rid_decoder.find(alias_id);
    if (dit == rid_decoder.end())
        return -1;

    uint64_t real_data = dit->second;
    uint64_t real_id = real_data >> 6;
    auto tid = task_map.find(real_id);
    if (tid == task_map.end())
        return -1;

    uint64_t image_id = real_id & 63;
    user& demo = user_vec[user_id];
    image_set& ims = tid->second;
    int avg = ims.add_rating(image_id, rating, demo);

    // add this ratingto user data for adjustment purposes,
    // if the average is not -1, which means
    if (avg != -1)
        demo.add_rating(rating, avg);

    if (++ims.ratings_total >= )
        finalize(alias_id, real_id);
    else
        regenerate_ids();

    db.insert(real_id, );
}

int get_image()
{
/*

SELECT * | select_expression | DISTINCT partition 
FROM [keyspace_name.] table_name 
[WHERE partition_value
   [AND clustering_filters 
   [AND static_filters]]] 
[ORDER BY PK_column_name ASC|DESC] 
[LIMIT N]
[ALLOW FILTERING]
*/

    SELECT ID, IMAGE
    FROM 
    WHERE 
    ORDER BY 
}

void login_db(const char* username, const uint8_t* password)
{

}

void login(const char* username, const uint8_t* password)
{
    auto uit = users.find(username);
    if (uit == users.end())
        return login_db();



    return memcmp(password, demo.password, 64) ? generate_cookie() : -1;
}

