#include <vector>

class rating_queue
{
    rating_dao& rdao_;
    experiment_dao& edao_;

    vector<pair<uint64_t, vector<likert_rating>>> ratings_by_user_;
    vector<pair<uint64_t, vector<likert_rating>>> ratings_by_image_;

    vector<elo_rating> elos_;
    vector<likert_rating> likerts_;

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

void insert_elos()
{
    // insert elo for database
}

void modify_biases()
{
    // update bias for each user in database
}

void insert_likerts()
{
    // insert likert for database
}

void modify_scores()
{
    // modify experiments to adjust their scores
}

void rating_queue::sync_ratings()
{
    slock_.lock();

    vector<elo_rating> new_elos;
    vector<likert_rating> new_likerts;

    new_elos.swap(elos_);
    new_likerts.swap(likerts_);

    thr = new std::thread([this](){
        insert_elos();
        modify_biases();
        insert_likerts();
        modify_experiments();
    });

    thr.join();
}

void rating_queue::add_elo(elo_rating er)
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

    if (likerts_.size() > 1000)
        sync_ratings();
}
