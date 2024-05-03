#pragma once

#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <iostream>


class HyperLogLog {
public:
    HyperLogLog(int b) : b(b), m(1 << b), M(m, 0) {}

    void add(uint32_t obj);

    double estimate() const;

    static uint32_t MurmurHash(uint32_t h);

    static uint8_t countTrailingZeros(uint32_t num);

    static uint32_t extractMSB(uint32_t num, int k);


private:
    int b, m;
    std::vector<uint8_t> M;
};


