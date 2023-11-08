// ImageModel.hpp
#ifndef IMAGE_MODEL_HPP
#define IMAGE_MODEL_HPP

#include <string>


K = 32
initial_SD = 150
confidence_level = 0.95
z_score = norm.ppf(1 - (1 - confidence_level) / 2)



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
	// ID for image in database
	uint64_t image_id_;

	// ID for experiment
	uint64_t experiment_id_;

	// The rank of this image in the experiment
	//uint32_t ranking_;

	// Total # of wins for paired tests
	uint32_t wins_;
	// Whether or not
	uint32_t is_complete_;

	// Elo rating
	uint32_t elo_rating_;
	// Elo change accumulator, important for variability
	uint32_t elo_ch_acc_;

	// total # of paired (elo) results (len for p_outcomes_)
	uint32_t total_paired_;
	// total # of singular (likert) results (len for p_outcomes_)
	uint32_t total_rating_;
	// 
	uint32_t total_comments_;

	// outcomes for paired
	uint8_t* p_outcomes_;

	// outcomes for singular
	uint32_t* tags_bitmap_;

	// list of all comments
	uint8_t* comments_;


	inline double rating_variability()
	{
		return sqrt(double(elo_ch_acc_) / (total_paired_ - 1));
	}

  inline void moe()
  {
    return 1.96 * (rating_variability() / sqrt(total_paired_));
  }

public:
	image_model(uint64_t id, uint64_t user_id, uint32_t tags);

	// Getters
	int get_id() const;
	int get_user_id() const;
	unsigned int getTagsBitmap() const;

	inline int elo() const
	{
		return elo_rating_;
	}

	// Setters
	void setTagsBitmap(unsigned int tagsBitmap);

	// Tag manipulation methods
	void addTag(int tagBit);
	void removeTag(int tagBit);
	bool hasTag(int tagBit) const;

	void add_comment();

	int add_compare(uint8_t other, uint8_t win, uint32_t change, pool_alloc& pa);

	void rate_image(uint8_t score, uint32_t tags, char* comment, uint8_t comment_len, pool_alloc& pa)
	{
		uint32_t

	}

};



int image_model::add_compare(uint8_t other, uint8_t win, uint32_t change, pool_alloc& pa)
{
	uint32_t tpair = total_paired_;
	uint32_t talloc = get_allocsz(tpair);

	if (tpair + 1 > talloc) {
		// allocate larger buffer
		uint8_t* new_alloc = pa.alloc(total_allocated << 1);

		// copy old buffer to new array
		memcpy(new_alloc, p_outcomes_, talloc);
		
		// deallocate old, smaller array
		pa.dealloc(p_outcomes_);

		p_outcomes_ = new_alloc;
	}

	// get position of current
	p_outcomes_[tpair] = (win << 7) | (other);
	elo_rating_ += change;
	elo_ch_acc_ += (change * change);

	++total_paired_;


	// check to see if this should be removed from queue
	if () {

	}
}








#endif // IMAGE_MODEL_HPP




