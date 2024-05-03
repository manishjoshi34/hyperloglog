# HyperLogLog

HyperLogLog is a probabilistic data structure used for estimating the cardinality (number of distinct elements) of a multiset. It achieves this with high accuracy and low memory usage compared to traditional counting methods.

## How it works

### Overview
HyperLogLog works by hashing elements of the set and using a set of registers to estimate the number of unique elements. It utilizes the observation that the number of leading zeros in the binary representation of a hash value follows a certain distribution, allowing for an estimation of the cardinality.

### Algorithm
The algorithm consists of the following key steps:

1. **Hashing**: Each element in the set is hashed to obtain a 32-bit hash value.
2. **Register selection**: Based on the hash value, a subset of bits (referred to as the "bucket" or "register") is selected from the hash value to identify the register to be updated.
3. **Register update**: The register is updated with the count of trailing zeros in the remaining bits of the hash value.
4. **Estimation**: Finally, the harmonic mean of the register values is computed, and a bias correction factor is applied to obtain the estimated cardinality.

### Equations
The key equations used in the HyperLogLog algorithm are as follows:

- **Register selection**: j = extractMSB\(x, b\), where \( x \) is the hash value, \( b \) is the number of bits used for register selection, and \( j \) is the index of the register to be updated.
- **Register update**: w = x<<b, \( M[j] = max\(M[j], countTrailingZeros\(w\)\), where \( M \) is the array of registers.
- **Estimation**:  E = alpha_m * m^2 * Z, where \( alpha_m \) is a bias correction factor, \( m \) is the number of registers, and \( Z \) is the harmonic mean of the register values.

## Usage
To use HyperLogLog in your project, simply include the provided header file `hyperloglog.hpp` and create an instance of the `HyperLogLog` class. You can then add elements to the data structure using the `add` method and estimate the cardinality using the `estimate` method.

## References
For more information about HyperLogLog, refer to the original paper by Flajolet et al. and subsequent research on improvements and optimizations.

- [Wikipedia: HyperLogLog](https://en.wikipedia.org/wiki/HyperLogLog)
