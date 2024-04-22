// ImageModel.hpp
#ifndef IMAGE_MODEL_HPP
#define IMAGE_MODEL_HPP

#include <string>

size_t get_allocsz(size_t N)
{
    size_t result = 1;

    // Continue multiplying by 64 until result is greater than N
    while (result <= N) {
        result <<= 6;
    }

    return result;
}

class image_model
{
	// total # of paired (elo) results (len for e_outcomes_)
	uint32_t total_elo_ : 15;
	// total # of singular (likert) results (len for e_outcomes_)
	uint32_t total_likert_ : 17;

	// Total # of wins for paired tests
	uint32_t total_wins_ : 22;
	// 0 = elo, 1 = likert, 2 = done
	uint32_t status_ : 2;
	// The rank of this image in the experiment
	uint32_t ranking_ : 8;

	// Elo rating
	uint32_t elo_rating_;
	// Elo change accumulator, important for variability
	uint32_t elo_change_;

	// total # of comments
	uint32_t total_comments_ : 15; 
	// total length of comments in bytes
	uint32_t total_comments_len_ : 17;

	// outcomes for paired [this is preallocated elsewhere ]
	// elo_model* e_outcomes_;

	// outcomes for likert with tags in bitmap fashion
	likert_model* l_outcomes_;

	// list of all comments
	uint8_t* comments_;

	inline double rating_variability()
	{
		return sqrt(double(elo_change_) / (total_elo_ - 1));
	}

	inline void moe()
	{
		return (rating_variability() / sqrt(total_elo_));
	}


public:
	image_model(uint64_t id, uint64_t user_id, uint32_t tags);

	// Getters
	int get_id() const;
	int get_user_id() const;
	unsigned int getTagsBitmap() const;


    size_t image_model::serialize(uint8_t* out);
};


void image_model::add_comment(uint8_t rating_idx, uint8_t* comment, uint8_t comment_len)
{
	// copy variables

	uint8_t* p = comments_;
	//
	total_comments_len_ += (comment_len + 2);
	++total_comments_;

	p += total_len;

	//
	WRITE8(p, rating_idx)

	//
	WRITE8(p, comment_len)

	//
	COPY_INC(p, comments, comment_len)
}


int image_model::clear()
{
	wins_ = 0;
	// 0 = elo, 1 = likert, 2 = done
	status_ = 0;

	elo_rating_ = 1000;
	elo_change_ = 0;

	// total # of paired (elo) results (len for e_outcomes_)
	total_elo_ = 0;
	// total # of singular (likert) results (len for e_outcomes_)
	total_likert_ = 0;
	// total # of comments
	total_comments_ = 0;

	// outcomes for paired
	dealloc(e_outcomes_);

	// outcomes for singular
	dealloc(l_outcomes_);
}

int image_model::update_elo(uint8_t other, uint8_t win, uint32_t change, pool_alloc& pa)
{
	uint32_t tpair = total_elo_;
	uint32_t talloc = get_allocsz(tpair);

	if (tpair + 1 > talloc) {
		// allocate larger buffer
		uint8_t* new_alloc = pa.alloc(total_allocated << 1);

		// copy old buffer to new array
		memcpy(new_alloc, e_outcomes_, talloc);
		
		// deallocate old, smaller array
		pa.dealloc(e_outcomes_);

		e_outcomes_ = new_alloc;
	}

	// get position of current
	e_outcomes_[tpair] = (win << 7) | (other);
	elo_rating_ += change;
	elo_change_ += (change * change);
	wins_ += win;

	++total_elo_;
}

int image_model::update_likert(uint8_t rating, uint32_t tags, const char* comment, uint32_t comment_len, pool_alloc& pa)
{
	l_outcomes_[total_likert_] = (uint32_t(rating) << 24) | tags;

	if (comment_len)
		add_comment(comment, comment_len);
}

/*
** Returns whether or not the image should be moved from elo state to
** likert state, or from likert state to finished state
*/
bool image_model::should_change_state(int rounds, double threshold)
{
    if (total_elo_ < rounds + 1)
        return false; // Not enough data to decide

    double totalChange = 0;
    for (uint32_t i = total_elo_ - rounds; i < total_elo_; ++i)
        totalChange += abs(e_outcomes_[i] - e_outcomes_[i - 1]);

    return (totalChange / rounds) < threshold;
}



size_t image_model::serialize(uint8_t* out)
{
}


#endif // IMAGE_MODEL_HPP


