
#ifndef ASTARSHORTESTPATH_ASTAR_H
#define ASTARSHORTESTPATH_ASTAR_H

#include <list>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <iostream>
#include <queue>
#include <memory>
#include <unordered_map>

#include "NodeGrid.h"

#endif //ASTARSHORTESTPATH_ASTAR_H

void AStar(NodeGrid& nodeGrid,
           std::unordered_map<Node, Node>& parentChildPairs,
           std::unordered_map<Node, double>& accumulatedCost) {
    const Node& startNode = nodeGrid.getStartNode();
    const Node& targetNode = nodeGrid.getTargetNode();

    PriorityQueue<Node, double> openSet;
    openSet.put(startNode, 0);

    parentChildPairs[startNode] = startNode;
    accumulatedCost[startNode] = 0;

    while (!openSet.empty()) {
        Node currentNode = openSet.get();

        if (currentNode == targetNode) {
            break;
        }

        for (const auto& neighborNode : nodeGrid.getNeighbors(currentNode)) {
            double new_cost = accumulatedCost[currentNode] + calcDistanceEuclidean(currentNode, neighborNode);

            if (accumulatedCost.find(neighborNode) == accumulatedCost.end()
                || new_cost < accumulatedCost[neighborNode]) {
                accumulatedCost[neighborNode];
                double priority = new_cost + calcDistanceEuclidean(neighborNode, targetNode);
                openSet.put(neighborNode, priority);
                parentChildPairs[neighborNode] = currentNode;
            }
        }
    }
}

void dijkstra_search(NodeGrid& nodeGrid,
                     std::unordered_map<Node, Node>& parentChildPairs,
                     std::unordered_map<Node, double>& accumulatedCost) {
    const Node& startNode = nodeGrid.getStartNode();
    const Node& targetNode = nodeGrid.getTargetNode();

    PriorityQueue<Node, double> openSet;
    openSet.put(startNode, 0);

    parentChildPairs[startNode] = startNode;
    accumulatedCost[startNode] = 0;

    while(!openSet.empty()) {
        Node currentNode = openSet.get();

        if (currentNode == targetNode) {
            std::cout << "Node found\n";
            break;
        }

        std::vector<Node> neighbors = nodeGrid.getNeighbors(currentNode);
        for (const auto& neighborNode : neighbors) {
            double new_cost = accumulatedCost[currentNode] + calcDistanceManhattan(currentNode, neighborNode);

            if (accumulatedCost.find(neighborNode) == accumulatedCost.end()
                || new_cost < accumulatedCost[neighborNode]) {
                accumulatedCost[neighborNode] = new_cost;
                parentChildPairs[neighborNode] = currentNode;
                openSet.put(neighborNode, new_cost);
            }
        }
    }
}

std::unordered_map<Node, Node> breadthFirstSearch(NodeGrid& nodeGrid) {
    const Node& startNode = nodeGrid.getStartNode();
    const Node& targetNode = nodeGrid.getTargetNode();

    std::queue<Node> openSet;
    openSet.push(startNode);

    std::unordered_map<Node, Node> parentChildPairs;
    parentChildPairs[startNode]  = startNode;

    int whileIterationNumber = 0;
    int forIterationNumber = 0;
    int nodePushNumber = 0;
    while (!openSet.empty()) {
        whileIterationNumber++;
        Node currentNode = openSet.front();
        openSet.pop();

        if (currentNode == targetNode) {
            std::cout << "Node found on while iteration " << whileIterationNumber << '\n';
            std::cout << "Node found on for iteration " << forIterationNumber << '\n';
            std::cout << "Node found on push " << nodePushNumber << '\n';
            break;
        }

        std::vector<Node> neighbors = nodeGrid.getNeighbors(currentNode);
        for (const auto& neighborNode : neighbors) {
            forIterationNumber ++;
            if (parentChildPairs.find(neighborNode) == parentChildPairs.end()) {
                nodePushNumber++;
                openSet.push(neighborNode);
                parentChildPairs[neighborNode] = currentNode;
            }
        }
    }

    return parentChildPairs;
}