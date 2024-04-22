#include <vector>

class rating_queue
{
    struct rating_data
    {
        int64_t ratings_sum;
        vector<likert_rating_model> ratings_list;
    };


    rating_dao& rdao_;
    experiment_dao& edao_;

    // user change
    unordered_map<pair<uint64_t, vector<likert_rating_model>>> ratings_by_user_;
    unordered_map<pair<uint64_t, vector<likert_rating_model>>> ratings_by_image_;

    vector<elo_rating_model> elos_;

    // also contains rating count
    vector<likert_rating_model> likerts_;

    int64_t sum_ratings_;

    spinlock slock_;
public:
    rating_queue(RatingDAO& dao);

    // put ratings into the database
    void sync_ratings();

    // adds likert rating
    void add_rating();

    // adds likert rating
    void add_elo();
};

void rating_queue::sync_ratings()
{
    slock_.lock();


    vector<elo_rating> new_elos;
    vector<likert_rating> new_likerts;

    new_elos.swap(elos_);
    new_likerts.swap(likerts_);

    thr = new std::thread([this](){
        // insert all elo ratings into the database
        insert_elos();

        // insert all elo ratings into the database
        modify_biases();
        insert_likerts();
        modify_experiments();
    });

    sum_ratings_ = 0;
    

    thr.join();
}


void rating_queue::add_elo(elo_rating_model& er)
{
    slock_.lock();

    elos_.push_back(er);

    if (elos_.size() > 1000)
        sync_ratings();
}

void rating_queue::add_likert(likert_rating lr)
{
    slock_.lock();
    
    likerts_.push_back(lr);

    auto it = ratings_by_user_.find();

    if (likerts_.size() > 1000)
        sync_ratings();
}



void rating_queue::insert_elos(vector<elo_rating_model>& elo_list)
{
    // insert elo for database
    string query;
    query.reserve();


    string query;
    query.reserve(elo_list.size() << 6);
    query += "INSERT INTO users(id,imgset_id,stdbias,user_id,win_idx,lose_idx,win_elo,lose_elo) VALUES"

    for (int i = 0; i < elo_list.size(); ++i) {
        auto obj = elo_list.at(i);

        query += "(0x";
        query += hex_itos(eo.imgset_id);
        query += ",0x";
        query += hex_itos(eo.image_idx);
        query += ",0x";
        query += hex_itos(eo.user_id);
        query += ",0x";
        query += hex_itos(eo.win_idx);
        query += ",0x";
        query += hex_itos(eo.lose_idx);
        query += ",0x";
        query += hex_itos(eo.win_elo);
        query += ",0x";
        query += hex_itos(eo.lose_elo);
        query += ")\n";
    }


    for () {
        // insert all elo ratings for one experiment into file

        // add total wins for image
        // add total elos for image
        // change elo score
    }
}

void rating_queue::modify_biases(vector<elo_rating_model>& elo_list)
{
    // update bias for each user in database
    // files are sharded for each 16777216 users


    /*
    INSERT INTO users (id, name, email)
    VALUES
        (1, 'John Doe', 'john@example.com'),
        (2, 'Jane Smith', 'jane@example.com')
    ON DUPLICATE KEY UPDATE
        name = VALUES(name),
        email = VALUES(email);
    */
    string query;
    query.reserve(elo_list.size() << 6);
    query += "INSERT INTO users(id,pctbias,stdbias,credits)"

    for (int i = 0; i < elo_list.size(); ++i) {
        auto bo = bias_list.at(i);

        query += "(0x";
        query += hex_itos(bo.user_id);
        query += ",0x";
        query += hex_itos(bo.pctbias);
        query += ",0x";
        query += hex_itos(bo.stdbias);
        query += ",0x";
        query += hex_itos(bo.credits);
        query += ")\n";
    }

    query += "ON DUPLICATE KEY UPDATE\n"
             "pctbias = VALUES(pctbias),\n"
             "stdbias = VALUES(stdbias),\n"
             "credits = VALUES(credits);\n";
}

void rating_queue::update_image_aggregates()
{
    /*
    INSERT INTO users (id, name, email)
    VALUES
        (1, 'John Doe', 'john@example.com'),
        (2, 'Jane Smith', 'jane@example.com')
    ON DUPLICATE KEY UPDATE
        name = VALUES(name),
        email = VALUES(email);
    */
    string query;
    query.reserve();
    query += "INSERT INTO images(id,total_elos,total_likerts,elo_wins,elo_score,likert_raw_sum,likert_adj_sum)"

    for (int i = 0; i < rows; ++i) {
        query += "(0x";
        query += hex_itos(obj.user_id);
        query += ",0x";
        query += hex_itos(obj.credits);
        query += ")\n";
    }
}

void rating_queue::update_experiment_aggregates()
{
}

void rating_queue::insert_likerts()
{
    // insert likert for database
    
    // for couchbase
    // Initialize the Couchbase cluster connection
    //cluster c("couchbase://127.0.0.1", "username", "password");
    auto bucket = c.open_bucket("bucket_name");

    // Example initial binary data
    std::string doc_id = "binary_document_id";

    // Retrieve the binary data
    auto result = bucket.get(doc_id);
    auto retrievedData = result.value(); // This is binary data

    // New data to append
    std::vector<uint8_t> newData = {/* new binary data bytes */};

    // Append new data to the retrieved data
    auto modifiedData = appendToBinaryData(retrievedData, newData);

    // Store the modified binary data back to Couchbase
    document doc;
    doc.value(modifiedData);
    bucket.upsert(doc);
}


// Function to append new data to existing binary data
std::vector<uint8_t> appendToBinaryData(const std::vector<uint8_t>& originalData, 
                                        const std::vector<uint8_t>& newData)
{
    std::vector<uint8_t> modifiedData = originalData;
    modifiedData.insert(modifiedData.end(), newData.begin(), newData.end());
    return modifiedData;
}

void modify_scores()
{
    // modify experiments to adjust their scores
}
