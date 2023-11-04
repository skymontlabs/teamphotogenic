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
    std::string getFilePath() const;
    unsigned int getTagsBitmap() const;

    // Setters
    void setTagsBitmap(unsigned int tagsBitmap);

    // Tag manipulation methods
    void addTag(int tagBit);
    void removeTag(int tagBit);
    bool hasTag(int tagBit) const;

private:
    uint64_t id;
    uint64_t userId;
    std::string filePath;
    uint32_t tagsBitmap; // Assuming 32 tags max, use uint64_t for 64 tags, etc.
};

#endif // IMAGE_MODEL_HPP
