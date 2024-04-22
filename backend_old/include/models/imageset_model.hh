// ExperimentModel.hpp
#ifndef EXPERIMENTMODEL_HPP
#define EXPERIMENTMODEL_HPP

#include <vector>
#include "image_model.hpp"

#define K = 32
#define initial_SD = 150
#define confidence_level = 0.95
#define z_score = norm.ppf(1 - (1 - confidence_level) / 2)

const int K = 32; // K-factor; you might want to adjust this value
const int roundsToCheck = 5; // Number of rounds to check for minor changes
const double changeThreshold = 5.0; // Threshold for minor change

struct likert_candidate
{
    uint32_t img_idx : 8;
    uint32_t elo_rating : 24;
};

class experiment_model
{
    // id of experiment
    uint64_t experiment_id_;

    // name of experiment
    char experiment_name[21];

    // 0=paused 1=elo 2=likert
    uint8_t status_;

    // Accuracy level
    uint8_t accuracy_;

    // limit is 255 images
    uint8_t total_images_;
    
    // how many images still running
    uint8_t total_candidates_;

    // cached # of elos
    uint32_t total_elos_;
    
    // 
    uint32_t total_likerts_;

    // image list
    image_model* images_;

    // likert candidates
    likert_candidate* lcs_;


public:
    experiment_model(int id, const char* name, const uint32_t name_len):
    total_elos_(0),
    total_likerts_(0),
    total_candidates_(0),
    status_(0),
    current_elo_(0),
    current_likert_(0),
    accuracy_(0),
    {}

    // this assumes images is already allocated
    void reinit(pool_allocator& pa, uint8_t* data)
    {
        experiment_id_ = READ64(p);
        
        uint8_t len = READ8(p);
        experiment_name[0] = len;
        COPY_INC(experiment_name+1, p, len)

        uint8_t n_images = READ8(p);
        images_ = pa.alloc();
        total_images_ = n_images;

        for (int i = 0; i < n_images; ++i) {
            p = images_[i].reinit(pa, p);
        }
    }

    uint8_t* serialize(uint8_t* out)
    {
        WRITE8(p, experiment_id_)

        WRITE8(p, total_images_)
        
        WRITE32(p, total_elos_)
        
        WRITE32(p, total_likerts_)
        
        for (int i = 0; i < total_images_; ++i) {
            p = images_[i].serialize(p);
        }

        return p;
    }


/*
void updateEloScores(Image &winner, Image &loser, int K) {
    double expectedScoreWinner = 1 / (1.0 + pow(10, (loser.eloScore - winner.eloScore) / 400.0));
    double expectedScoreLoser = 1 / (1.0 + pow(10, (winner.eloScore - loser.eloScore) / 400.0));

    int newWinnerScore = winner.eloScore + round(K * (1 - expectedScoreWinner));
    int newLoserScore = loser.eloScore + round(K * (0 - expectedScoreLoser));

    winner.updateElo(newWinnerScore);
    loser.updateElo(newLoserScore);
}
*/
    void fetch_rand_2image()
    {
        int r = rand(total_candidates_);

        
    }

    void switch_likert()
    {
        sort(lcs_, lcs_ + total_candidates_, [](likert_candidate& l0, likert_candidate& l1)
        {
            return l0.elo_rating < l1.elo_rating;
        });
        // loop to each image, pausing it if not in candidates
    }


    int add_elo_pair(uint32_t win_idx, uint32_t lose_idx, pool_alloc& pa)
    {
        auto& winner = images_[win_idx];
        auto& loser = images_[lose_idx];

        double expectedScoreWinner = 1 / (1.0 + pow(10, (loser.elo() - winner.elo()) / 400.0));
        double expectedScoreLoser = 1 / (1.0 + pow(10, (winner.elo() - loser.elo()) / 400.0));

        winner.update_elo(lose_idx, 1, round(K * (1 - expectedScoreWinner)), pa);
        loser.update_elo(win_idx, 0, round(K * (0 - expectedScoreLoser)), pa);

        // decide if either one
        if (winner.should_change_state()) {
            // if not enough others rated yet, put into 
            // if very poor elo score, 
            winner.pause();
            PUSH_ARRAY(lcs_, total_candidates_, likert_candidate(winner.idx(), winner.elo()))
        }

        if (loser.should_change_state()) {
            loser.pause();
            PUSH_ARRAY(lcs_, total_candidates_, likert_candidate(loser.idx(), loser.elo()))
        }

        if (total_candidates_ > 25 || total_candidates_ > (total_images_ >> 1)) {
            switch_likert();
        }
    }

    int add_likert(uint32_t image_idx, pool_alloc& pa)
    {
        auto& img = images_[image_idx];

        img.update_likert(, pa);
    }
};

#endif // EXPERIMENTMODEL_HPP
