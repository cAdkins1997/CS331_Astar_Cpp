
#include <thread>
#include "Pathfinding.h"

void printImportantNodes(const NodeGrid& nodeGrid) {
    std::cout << "Start Node = [" << nodeGrid.getStartNode().getXLocation() << "][" << nodeGrid.getStartNode().getYLocation() << "]\n";
    std::cout << "Target Node = [" << nodeGrid.getTargetNode().getXLocation() << "][" << nodeGrid.getTargetNode().getYLocation() << "]\n";
}

void printPath(const std::vector<Node>& path) {
    for (auto node : path) {
        int xLocation = node.getXLocation();
        int yLocation = node.getYLocation();
        std::cout << "Visiting Node: [" << xLocation << "][" << yLocation << "] \n";
    }
}

int main() {
    std::vector<NodeGrid> nodeGrids;
    for (unsigned int i = 0; i < 100; i++) {
        NodeGrid nodeGrid = NodeGrid();
        nodeGrids.push_back(nodeGrid);
    }

    for (auto grid : nodeGrids) {
        printImportantNodes(grid);
        grid.generateObstacles();
        std::unordered_map<Node, Node> came_from;
        std::unordered_map<Node, double> cost_so_far;
        grid.AStar(came_from, cost_so_far);
        std::vector<Node> path = grid.reconstructPath(came_from);
        grid.printGridTypes();
        std::cout << '\n' << '\n';
    }
}
