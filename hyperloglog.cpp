#include "hyperloglog.hpp"

#include <algorithm>

uint32_t 
HyperLogLog::extractMSB(uint32_t num, int k) {
    // Shift right to discard the least significant bits
    num >>= (32 - k);
    
    // Apply a mask to keep only the k most significant bits
    uint32_t mask = (1 << k) - 1;
    num &= mask;
    
    return num;
}

uint8_t 
HyperLogLog::countTrailingZeros(uint32_t num) {
    if (num == 0)
        return 32; // If the number is zero, all bits are zeros
    
    uint8_t count = 0;
    // Loop while the least significant bit is zero
    while ((num & 1) == 0) {
        count++;
        // Shift the number to the right by one bit
        num >>= 1;
    }
    return count;
}

void 
HyperLogLog::add(uint32_t obj) {
    uint32_t x = HyperLogLog::MurmurHash(obj);
    uint32_t j = HyperLogLog::extractMSB(x,b); // use the first b bits as index
    uint32_t w = x << b; // remaining bits as bit sequence
    M[j] = std::max(M[j], HyperLogLog::countTrailingZeros(w));
}


double 
HyperLogLog::estimate() const {
    double alpha_m = (m == 16) ? 0.673
                    : (m == 32) ? 0.697
                    : (m == 64) ? 0.709
                    : 0.7213 / (1 + 1.079 / m);
    double acc = 0.0;
    for(auto val : M){
        acc += std::pow(2.0, -val);
    }
    double Z = 1.0 / acc;
    double E = alpha_m * m * m * Z;
    return E;
}


uint32_t 
HyperLogLog::MurmurHash(uint32_t h) {
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;
    return h;
}
