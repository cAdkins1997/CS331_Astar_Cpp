//
// Created by ulver on 9/22/2023.
//

#ifndef ASTARSHORTESTPATH_ASTARUTILITY_H
#define ASTARSHORTESTPATH_ASTARUTILITY_H

#include <cmath>
#include <random>

#include "Node.h"

#endif //ASTARSHORTESTPATH_ASTARUTILITY_H

template <typename T> T aStarRandom(T min, T max)
{
    std::random_device random;
    std::mt19937_64 generator(random());
    std::uniform_real_distribution<> distribution(min, max);
    return distribution(generator);
}

template <typename T> T clamp(T number, T min, T max)
{
    if (number < min) {
        return min;
    } else if (number > max) {
        return max;
    }
    return number;
}


namespace std
{
    template<>
    struct hash<Node>
    {
        size_t operator()(const Node& _node) const noexcept
        {
            return hash<int>()(_node.getId());
        }
    };
}

template<typename T, typename priority_t>
struct PriorityQueue {
    typedef std::pair<priority_t, T> PQElement;
    std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> elements;

    inline bool empty() const {
        return elements.empty();
    }

    inline void put(T item, priority_t priority) {
        elements.emplace(priority, item);
    }

    T get() {
        T best_item = elements.top().second;
        elements.pop();
        return best_item;
    }
};