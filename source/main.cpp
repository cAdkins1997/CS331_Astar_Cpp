
#include <thread>
#include "Pathfinding.h"

void printImportantNodes(const NodeGrid& nodeGrid) {
    std::cout << "Start Node = [" << nodeGrid.getStartNode().getXLocation() << "][" << nodeGrid.getStartNode().getYLocation() << "]\n";
    std::cout << "Target Node = [" << nodeGrid.getTargetNode().getXLocation() << "][" << nodeGrid.getTargetNode().getYLocation() << "]\n";
}

void printPath(const std::vector<Node>& path) {
    for (const auto& node : path) {
        int xLocation = node.getXLocation();
        int yLocation = node.getYLocation();
        std::cout << "Visiting Node: [" << xLocation << "][" << yLocation << "] \n";
    }
    std::cout << "\n";
}

int main() {
    NodeGrid nodeGrid = NodeGrid();
    printImportantNodes(nodeGrid);
    nodeGrid.printGridTypes();
    std::unordered_map<Node, Node> parentChildPairs;
    std::unordered_map<Node, double> accumulatedCost;
    AStar(nodeGrid, parentChildPairs, accumulatedCost);
    std::vector<Node> path = nodeGrid.reconstructPath(parentChildPairs);
    printPath(path);
    nodeGrid.printGridTypes();
}