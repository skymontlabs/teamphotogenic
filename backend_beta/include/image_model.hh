// ImageModel.hpp
#ifndef IMAGE_MODEL_HPP
#define IMAGE_MODEL_HPP

#include <string>

class ImageModel {
public:
    ImageModel(int id, int userId, const std::string& filePath, unsigned int tagsBitmap);

    // Getters
    int getId() const;
    int getUserId() const;
    unsigned int getTagsBitmap() const;

    // Setters
    void setTagsBitmap(unsigned int tagsBitmap);

    // Tag manipulation methods
    void addTag(int tagBit);
    void removeTag(int tagBit);
    bool hasTag(int tagBit) const;

    void add_comment

private:
    uint64_t id;
    uint64_t user_id;
    uint64_t experiment_id;
    uint32_t tags_bitmap; // Assuming 32 tags max, use uint64_t for 64 tags, etc.
    vector<uint8_t> comments_;
};

#endif // IMAGE_MODEL_HPP
