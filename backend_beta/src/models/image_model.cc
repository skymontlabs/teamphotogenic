// ImageModel.cpp
#include "ImageModel.hpp"

ImageModel::ImageModel(int id, int userId, const std::string& filePath, unsigned int tagsBitmap)
    : id(id), userId(userId), filePath(filePath), tagsBitmap(tagsBitmap) {}

int ImageModel::getId() const {
    return id;
}

int ImageModel::getUserId() const {
    return userId;
}

std::string ImageModel::getFilePath() const {
    return filePath;
}

unsigned int ImageModel::getTagsBitmap() const {
    return tagsBitmap;
}

void ImageModel::setTagsBitmap(unsigned int newTagsBitmap) {
    tagsBitmap = newTagsBitmap;
}

void ImageModel::addTag(int tagBit) {
    tagsBitmap |= (1 << tagBit);
}

void ImageModel::removeTag(int tagBit) {
    tagsBitmap &= ~(1 << tagBit);
}

bool ImageModel::hasTag(int tagBit) const {
    return (tagsBitmap & (1 << tagBit)) != 0;
}
