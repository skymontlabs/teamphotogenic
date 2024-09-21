#include <string>
#include <vector>
#include <ctime>

// User struct
struct User {
    long long user_id;

    char* email;
    char* phone;
    
    int credits;
    int status;
    
    uint8_t* password; // 96 bytes, password (64), salt (16), seed (16) 
    
    std::time_t created_at;

    User() : password(64), salt(16) {}
};

// ImageSet struct
struct ImageSet {
    long long image_set_id;
    long long user_id;

    std::string title; // 32 chars

    int total_pairs = 0;
    int total_likerts = 0;
    int total_pts = 0;
    int target_pairs;
    int target_likerts;
    int target_pts;
    int total_images = 0;

    unsigned char status = 0;
    std::time_t created_at;
};

// Image struct
struct Image {
    uint64_t image_id;
    uint64_t imageset_id : 56;
    uint64_t series_id : 8;

    uint64_t user_id;
    
    uint32_t total_pairs;
    uint32_t total_likerts;

    uint32_t pairs_wins;
    uint32_t pairs_score;
    
    int likert_raw_sum;
    int likert_adj_sum;
    std::time_t upload_time;
};

// LikertRating struct
struct LikertRating {
    long long likert_id;
    long long imageset_id;
    long long image_id;
    long long rater_user_id;
    int rating_value;
    std::time_t rating_time;
};

// PairsRating struct
struct PairsRating {
    long long pairs_id;
    long long imageset_id;
    long long rater_user_id;
    long long recv_user_id;
    unsigned char winner_idx;
    unsigned char loser_idx;
    int winner_pairs;
    int loser_pairs;
    std::time_t rating_time;
};
