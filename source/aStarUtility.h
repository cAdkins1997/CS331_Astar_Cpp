
#ifndef ASTARSHORTESTPATH_ASTARUTILITY_H
#define ASTARSHORTESTPATH_ASTARUTILITY_H

#include <cmath>
#include <random>
#include <type_traits>
#include <chrono>
#include <functional>
#include <iostream>

#include "Node.h"

#endif //ASTARSHORTESTPATH_ASTARUTILITY_H

template<typename T>
concept arithmetic_type = std::is_arithmetic_v<T>;

auto aStarRandom(const arithmetic_type auto min, const arithmetic_type auto max)
{
    std::random_device random;
    std::mt19937_64 generator(random());
    std::uniform_real_distribution<> distribution(min, max);
    return distribution(generator);
}

[[maybe_unused]] auto clamp(const arithmetic_type auto number, const arithmetic_type auto min, const arithmetic_type auto max)
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