#include <iostream>
#include <cstdint>
#include <random>
#include <unordered_set>

#include "hyperloglog.hpp"

int main() {
    // Create a HyperLogLog object with a precision of 10 bits
    HyperLogLog hll(2);

    // Create a set to store the actual unique numbers
    std::unordered_set<uint32_t> unique_numbers;

    // Create a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    // Generate 10,000 random numbers
    for (int i = 0; i < 100000; ++i) {
        uint32_t num = dis(gen);
        hll.add(num);
        unique_numbers.insert(HyperLogLog::MurmurHash(num));
    }

    // Print the estimated and actual number of unique numbers
    std::cout << "Estimated unique numbers: " << hll.estimate() << std::endl;
    std::cout << "Actual unique numbers: " << unique_numbers.size() << std::endl;

    return 0;
}
