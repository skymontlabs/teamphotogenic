#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cmath>
#include <limits>
#include <algorithm>


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


// Enhanced Enum for age groups with explicit underlying type
enum AgeGroup : int {
    AGE_18_24 = 0,
    AGE_25_29,
    AGE_30_39,
    AGE_40_49,
    AGE_50_PLUS
};

// Improved function to generate a demographic key
int generateDemographicKey(AgeGroup age, char gender) {
    int genderBit = (gender == 'M' ? 1 : (gender == 'F' ? 2 : 0)); // Extended for non-binary options
    return (static_cast<int>(age) << 2) | genderBit; // Increased shift to accommodate expanded gender encoding
}

class RatingsBatch
{
public:
    struct Rating {
        int userId;
        int movieId;
        int imagesetId;
        int rating;
        AgeGroup age;
        char gender;
    };

private:
    std::vector<Rating> ratings;
    long long globalSum; // Changed to long long for larger data handling
    int globalCount;
    
    std::unordered_map<int, std::pair<int, int>> imagesetSumAndCount;
    std::pair<int, int> demographicSumAndCount[5 * 2];
    std::unordered_map<int, std::pair<double, double>> userStatsCache; // Cache for user stats, using double for higher precision


    // Constants for anomaly detection
    const double ANOMALY_STD_DEV_MULTIPLIER = 3.0; // Threshold for anomaly detection

    // Anomaly detection logic
    bool isAnomalous(const Rating& rating)
    {
        auto userStats = calculateUserMeanAndStdDev(rating.userId);
        double mean = userStats.first;
        double stdDev = userStats.second;
        double deviation = std::abs(rating.rating - mean);

        // Flag as anomalous if the rating deviates more than the threshold
        return (stdDev > 0) && (deviation > ANOMALY_STD_DEV_MULTIPLIER * stdDev);
    }


    // Calculate mean and standard deviation for a user with caching
    std::pair<double, double> calculateUserMeanAndStdDev(int userId)
    {
        if (userStatsCache.find(userId) != userStatsCache.end()) {
            return userStatsCache[userId];
        }

        double sum = 0.0, sumSq = 0.0;
        int count = 0;

        for (const auto& r : ratings) {
            if (r.userId == userId) {
                sum += r.rating;
                sumSq += r.rating * r.rating;
                count++;
            }
        }

        if (count == 0) {
            return {0.0, 0.0};
        }

        double mean = sum / count;
        double variance = (sumSq / count) - (mean * mean);
        double stdDev = std::sqrt(variance);

        userStatsCache[userId] = {mean, stdDev}; // Caching the result
        return {mean, stdDev};
    }

    // Calculate importance weights for users
    std::unordered_map<int, double> calculateImportanceWeights()
    {
        std::unordered_map<int, double> weights;

        for (const auto& r : ratings) {
            if (weights.find(r.userId) == weights.end()) {
                auto userStats = calculateUserMeanAndStdDev(r.userId);
                double weight = 1.0 / (1.0 + userStats.second); // Example weighting
                weights[r.userId] = weight;
            }
        }

        return weights;
    }

    // Z-Score normalization for a single rating
    int zScoreAdjustment(const Rating& r, double mean, double stdDev)
    {
        return stdDev > 0 ? static_cast<int>((r.rating - mean) / stdDev) : 0;
    }

    // Bayesian average calculation (placeholder)
    double bayesianAverage(int movieId, int minRatings)
    {
        // Implement Bayesian average calculation here

        avgScoreGlobal * minRatings1 + avgScoreGroup * minRatings2 + avgScoreUser * minRatings3 + sumScore
        ----------------------------------------------------------
        minRatings1 + minRatings2 + minRatings3 + numScore

        return 0.0;
    }

    // Bayesian average calculation (placeholder)
    double bayesianAverage4(int movieId, int minRatings)
    {
        // Implement Bayesian average calculation here

        /*
            let's say i have a situation where users must rate images by quality. however, images are uploaded in image sets.
            afterwards, i will then try to adjust user ratings by bias, and so will be using some form of bayesian averaging.

            users will have demographic data taken from them, which includes age group and gender. this goes for both uploaders and raters.

            generally, there are two averages in the numerator, that being the global average of all ratings. of the following, different subaverages,
            which would be the most important as well to include to neutralize bias:

            - average score by rater themselves
            - average score by uploader themselves
            - average score by age group (rater's group)
            - average score by age group (uploader's group)
            - average score by gender of uploader being rated by gender of rater (i.e. men rating women or women rating men, so 4 options),
                it's also important to debias male results towards women
            - average score by age group of uploader being rated by age group of rater
            - average score by imageset (as a whole)
            - average score by imageset (of the user rating the images there, so much smaller sample size)

            there's a lot more combinations but which would be the best (also please come up with more if there are some you think are good)
        */
        // ranked by importance

        avgScoreGlobal * minRatings1 + avgScoreGroup * minRatings2 + avgScoreUser * minRatings3 + avgScoreGroup * minRatings4 + sumScore
        -------------------------------------------------------------------------------------------------------------------------------------
        minRatings1 + minRatings2 + minRatings3 + minRatings4 + numScore

        return 0.0;
    }

    void refresh_averages()
    {
        globalSum >>= 1;
        globalCount >>= 1;

        for (int i = 0; i < 10; ++i)
            demographicSumAndCount[i] = std::make_pair(0,0);

    }

public:
    RatingsBatch():
    globalSum(0),
    globalCount(0) {}


    void addRating(int userId, int movieId, uint32_t imagesetId, uint32_t rating, AgeGroup age, char gender)
    {
        ratings.push_back({userId, movieId, imagesetId, rating, age, gender});
        globalSum += rating;
        globalCount++;

        //int groupKey = imagesetId;
        auto it = imagesetSumAndCount.find();
        if (it != imagesetSumAndCount.end()) {
            it->second.first += rating;
            it->second.second++;
        } else {
            it->second = std::make_pair(rating, 1);
        }
        
        int demographicKey = generateDemographicKey(age, gender);
        demographicSumAndCount[demographicKey].first += rating;
        demographicSumAndCount[demographicKey].second++;
    }

    void adjustRatings()
    {
        ratings.erase(std::remove_if(ratings.begin(), ratings.end(), 
                    [this](const Rating& r) { return isAnomalous(r); }), ratings.end());

        auto importanceWeights = calculateImportanceWeights();


        for (auto& r : ratings) {
            auto userStats = calculateUserMeanAndStdDev(r.userId);
            r.rating = zScoreAdjustment(r, userStats.first, userStats.second);
            r.rating = static_cast<int>(bayesianAverage(r.movieId, 5));
        }
    }

    double getGlobalAverage() const
    {
        return (globalCount > 0) ? static_cast<double>(globalSum) / globalCount : 0.0;
    }

    double getGroupAverage(uint32_t imagesetId) const
    {
        auto it = imagesetSumAndCount.find(imagesetId);
        if (it != imagesetSumAndCount.end() && it->second.second > 0)
            return it->second.first / it->second.second;

        return 0.0;
    }

    double getDemographicAverage(AgeGroup age, char gender) const
    {
        int key = generateDemographicKey(age, gender);

        if (demographicSumAndCount[key].second > 0)
            return double(demographicSumAndCount[key].first) / double(demographicSumAndCount[key].second);

        return 0.0;
    }
};

// Main function
int main() {
    for (int i = 0; i < rows; ++i) {
        RatingsBatch batch;

        addRating(userId, movieId, imagesetId, rating, AgeGroup age, 'M');

        // Adjusting ratings
        if (i % 16384 == 0 && i > 0)
            batch.adjustRatings();
    }


    // Getting averages after adjustment
    std::cout << "Global Average After Adjustment: " << batch.getGlobalAverage() << std::endl;
    std::cout << "Group 1 Average After Adjustment: " << batch.getGroupAverage(1) << std::endl;
    std::cout << "Demographic (25, M) Average After Adjustment: " << batch.getDemographicAverage(AGE_25_29, 'M') << std::endl;

    return 0;
}

int main()
{
    FILE *file = fopen("ratings64.bin", "rb");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Determine the file size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the entire file
    uint64_t *buffer = malloc(fileSize);
    if (buffer == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return 1;
    }

    // Read the file into memory
    fread(buffer, 1, fileSize, file);
    fclose(file);

    // Process each line
    int numberOfLines = fileSize / sizeof(uint64_t);
    for (int i = 0; i < numberOfLines; i++) {
        uint64_t line = buffer[i];

        // Assuming little-endian byte order
        uint32_t userId = line & 0xFFFFFF;            // Extract 24-bit user id
        uint8_t rating = (line >> 24) & 0xFF;         // Extract 8-bit rating
        uint16_t movieId = (line >> 32) & 0xFFFF;    // Extract 16-bit movie id
        uint16_t days = (line >> 48) & 0xFFFF;       // Extract 16-bit days

        printf("Line %d - User ID: %u, Rating: %u, Movie ID: %u, Days: %u\n",
               i + 1, userId, rating, movieId, days);
    }

    // Free the allocated memory
    free(buffer);

    return 0;
}


