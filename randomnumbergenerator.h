#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H
#include <random>

class RandomNumberGenerator {
private:
    std::mt19937 gen;
public:
    RandomNumberGenerator() : gen(std::random_device{}()) {}

    int getRandomInt(int min, int max) {
        std::uniform_int_distribution<int> dis(min, max);
        return dis(gen);
    }
};
#endif // RANDOMNUMBERGENERATOR_H
