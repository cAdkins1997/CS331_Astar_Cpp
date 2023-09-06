#pragma once
#include <random>

template <typename T> T aStarRandom(T min, T max)
{
    std::random_device random;
    std::mt19937_64 generator(random());
    std::uniform_real_distribution<> distribution(min, max);
    return distribution(generator);
}

inline void printNodeVector(const std::vector<Node>& vector, const std::string& descriptionMessage) {
    std::cout << descriptionMessage << std::endl;

    for (unsigned int i = 0; i < vector.size(); i++) {
        std::cout << "f_cost for Node: " << i << " is: " << vector[i].f_Cost() << std::endl;
    }

    std::cout << std::endl;
}