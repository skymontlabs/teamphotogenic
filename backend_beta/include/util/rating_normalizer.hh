#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cmath>
#include <limits>
#include <algorithm>

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
        int groupId;
        int rating;
        AgeGroup age;
        char gender;
    };

private:
    std::vector<Rating> ratings;
    long long globalSum; // Changed to long long for larger data handling
    int globalCount;
    std::unordered_map<int, std::pair<double, int>> groupSumAndCount; // Using double for higher precision
    std::unordered_map<int, std::pair<double, int>> demographicSumAndCount; // Using double for higher precision
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
    std::unordered_map<int, double> calculateImportanceWeights() {
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
    int zScoreAdjustment(const Rating& r, double mean, double stdDev) {
        return stdDev > 0 ? static_cast<int>((r.rating - mean) / stdDev) : 0;
    }

    // Bayesian average calculation (placeholder)
    double bayesianAverage(int movieId, int minRatings) {
        // Implement Bayesian average calculation here
        return 0.0;
    }

public:
    RatingsBatch() : globalSum(0), globalCount(0) {}

    void addRating(int userId, int movieId, int groupId, int rating, AgeGroup age, char gender) {
        if (rating < 0) {
            std::cerr << "Error: Negative rating not allowed." << std::endl;
            return;
        }

        ratings.push_back({userId, movieId, groupId, rating, age, gender});
        globalSum += rating;
        globalCount++;
        int groupKey = groupId;
        groupSumAndCount[groupKey].first += rating;
        groupSumAndCount[groupKey].second++;
        int demographicKey = generateDemographicKey(age, gender);
        demographicSumAndCount[demographicKey].first += rating;
        demographicSumAndCount[demographicKey].second++;
    }

    void adjustRatings() {
        ratings.erase(std::remove_if(ratings.begin(), ratings.end(), 
                    [this](const Rating& r) { return isAnomalous(r); }), ratings.end());

        auto importanceWeights = calculateImportanceWeights();

        for (auto& r : ratings) {
            auto userStats = calculateUserMeanAndStdDev(r.userId);
            r.rating = zScoreAdjustment(r, userStats.first, userStats.second);
            r.rating = static_cast<int>(bayesianAverage(r.movieId, 5));
        }
    }

    double getGlobalAverage() const {
        return (globalCount > 0) ? static_cast<double>(globalSum) / globalCount : 0.0;
    }

    double getGroupAverage(int groupId) const {
        auto it = groupSumAndCount.find(groupId);
        if (it != groupSumAndCount.end() && it->second.second > 0) {
            return it->second.first / it->second.second;
        }
        return 0.0;
    }

    double getDemographicAverage(AgeGroup age, char gender) const {
        int key = generateDemographicKey(age, gender);
        auto it = demographicSumAndCount.find(key);
        if (it != demographicSumAndCount.end() && it->second.second > 0) {
            return it->second.first / it->second.second;
        }
        return 0.0;
    }
};

// Main function
int main() {
    RatingsBatch batch;

    // Adding some ratings
    batch.addRating(1, 101, 1, 5, AGE_25_29, 'M');
    batch.addRating(1, 102, 1, 4, AGE_25_29, 'M');
    batch.addRating(2, 103, 2, 3, AGE_30_39, 'F');
    batch.addRating(2, 104, 2, 2, AGE_30_39, 'F');

    // Adjusting ratings
    batch.adjustRatings();

    // Getting averages after adjustment
    std::cout << "Global Average After Adjustment: " << batch.getGlobalAverage() << std::endl;
    std::cout << "Group 1 Average After Adjustment: " << batch.getGroupAverage(1) << std::endl;
    std::cout << "Demographic (25, M) Average After Adjustment: " << batch.getDemographicAverage(AGE_25_29, 'M') << std::endl;

    return 0;
}
