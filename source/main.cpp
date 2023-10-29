
#include <thread>
#include <chrono>
#include "Pathfinding.h"

void printPath(const std::vector<Node>& path) {
    for (const auto& node : path) {
        int xLocation = node.getXLocation();
        int yLocation = node.getYLocation();
        std::cout << "Visiting Node: [" << xLocation << "][" << yLocation << "] \n";
    }
    std::cout << "\n";
}

int main() {
    auto nodeGrid = NodeGrid("../resources/obstacles.csv");
    nodeGrid.printImportantNodes();
    nodeGrid.printGridTypes();
    std::unordered_map<Node, Node> parentChildPairs;
    std::unordered_map<Node, double> accumulatedCost;
    AStar(nodeGrid, parentChildPairs, accumulatedCost);
    std::vector<Node> path = nodeGrid.reconstructPath(parentChildPairs);

    if (path.empty()) {
        std::cout << "could not find a path to target node \n";
    }

    printPath(path);
    nodeGrid.printGridTypes();
}