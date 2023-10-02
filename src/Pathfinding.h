
#ifndef ASTARSHORTESTPATH_ASTAR_H
#define ASTARSHORTESTPATH_ASTAR_H

#include <list>
#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>

#include "NodeGrid.h"

#endif //ASTARSHORTESTPATH_ASTAR_H

inline std::vector<Node> reconstructPath(const NodeGrid& nodeGrid, std::unordered_map<Node, Node>& came_from) {
    Node startNode = nodeGrid.getStartNode();
    Node targetNode = nodeGrid.getTargetNode();

    std::vector<Node> path;
    Node currentNode = targetNode;

    if (came_from.find(targetNode) == came_from.end()) {
        return path;
    }

    while (currentNode != startNode) {
        path.push_back(currentNode);
        currentNode = came_from[currentNode];
    }
    path.push_back(startNode);
    std::reverse(path.begin(), path.end());

    return path;
}

inline void AStar(NodeGrid& nodeGrid,
                  std::unordered_map<Node, Node>& came_from,
                  std::unordered_map<Node, double>& cost_so_far) {
    Node startNode = nodeGrid.getStartNode();
    Node targetNode = nodeGrid.getTargetNode();

    PriorityQueue<Node, double> open;
    open.put(startNode, 0);

    came_from[startNode] = startNode;
    cost_so_far[startNode] = 0;

    while (!open.empty()) {
        Node currentNode = open.get();

        if (currentNode == targetNode) {
            break;
        }

        for (auto neighborNode : nodeGrid.getNeighbors(currentNode)) {
            double new_cost = cost_so_far[currentNode] + calcDistanceManhattan(currentNode, neighborNode);

            if (cost_so_far.find(neighborNode) == cost_so_far.end()
                || new_cost < cost_so_far[neighborNode]) {
                cost_so_far[neighborNode];
                double priority = new_cost + calcDistanceManhattan(neighborNode, targetNode);
                open.put(neighborNode, priority);
                came_from[neighborNode] = currentNode;
            }
        }
    }
}

inline void dijkstra_search(NodeGrid& nodeGrid,
                            std::unordered_map<Node, Node>& came_from,
                            std::unordered_map<Node, double>& cost_so_far) {
    Node startNode = nodeGrid.getStartNode();
    Node targetNode = nodeGrid.getTargetNode();

    PriorityQueue<Node, double> open;
    open.put(startNode, 0);

    came_from[startNode] = startNode;
    cost_so_far[startNode] = 0;

    while(!open.empty()) {
        Node currentNode = open.get();

        if (currentNode == targetNode) {
            std::cout << "Node found\n";
            break;
        }

        std::vector<Node> neighbors = nodeGrid.getNeighbors(currentNode);
        for (auto neighborNode : neighbors) {
            double new_cost = cost_so_far[currentNode] + calcDistanceManhattan(currentNode, neighborNode);

            if (cost_so_far.find(neighborNode) == cost_so_far.end()
            || new_cost < cost_so_far[neighborNode]) {
                cost_so_far[neighborNode] = new_cost;
                came_from[neighborNode] = currentNode;
                open.put(neighborNode, new_cost);
            }
        }
    }
}

inline std::unordered_map<Node, Node> breadthFirstSearch(NodeGrid& nodeGrid) {
    Node startNode = nodeGrid.getStartNode();
    Node targetNode = nodeGrid.getTargetNode();

    std::queue<Node> open;
    open.push(startNode);

    std::unordered_map<Node, Node> came_from;
    came_from[startNode]  = startNode;
    
    while (!open.empty()) {
        Node currentNode = open.front();
        open.pop();

        if (currentNode == targetNode) {
            break;
        }

        std::vector<Node> neighbors = nodeGrid.getNeighbors(currentNode);
        for (auto neighborNode : neighbors) {
            if (came_from.find(neighborNode) == came_from.end()) {
                open.push(neighborNode);
                came_from[neighborNode] = currentNode;
            }
        }
    }

    return came_from;
}