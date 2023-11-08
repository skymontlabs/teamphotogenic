#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include "xxhash.h" // Make sure to include the xxHash library header.

class bloom_filter {
    uint64_t* bitArray;
    size_t arraySize;

    // We will use a small number of seeds and secrets for the example.
    // In a real application, you might want to have more, and they should be generated securely.
    std::vector<uint64_t> seeds {123456789, 987654321, 192837465};
    std::vector<std::string> secrets {"my_secret1", "my_secret2", "my_secret3"};

public:
    bloom_filter(size_t bitArrayByteSize) {
        arraySize = bitArrayByteSize / sizeof(uint64_t);
        bitArray = new uint64_t[arraySize];
        std::memset(bitArray, 0, bitArrayByteSize);
    }

    ~bloom_filter() {
        delete[] bitArray;
    }

    void add(const uint8_t* item, uint32_t len) {
        for (size_t i = 0; i < seeds.size(); ++i) {
            const void* secret = static_cast<const void*>(secrets[i].c_str());
            size_t secretSize = secrets[i].length();

            uint64_t hashValue = XXH3_64bits_withSecretandSeed(item, len, seeds[i], secret, secretSize);
            bitArray[hashValue % arraySize] |= (uint64_t(1) << (hashValue % 64));
        }
    }

    bool contains(const uint8_t* item, uint32_t len) const {
        for (size_t i = 0; i < seeds.size(); ++i) {
            const void* secret = static_cast<const void*>(secrets[i].c_str());
            size_t secretSize = secrets[i].length();

            uint64_t hashValue = XXH3_64bits_withSecretandSeed(item, len, seeds[i], secret, secretSize);
            if ((bitArray[hashValue % arraySize] & (uint64_t(1) << (hashValue % 64))) == 0) {
                return false; // If any of the bits is not set, the item is definitely not in the set.
            }
        }
        return true; // If all bits are set, the item is possibly in the set.
    }
};
