
#include <numeric>

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

    std::vector<double> executionTimes;
    for (auto grid : nodeGrids) {
        clock_t start = clock();
        printImportantNodes(grid);
        std::unordered_map<Node, Node> came_from;
        std::unordered_map<Node, double> cost_so_far;
        AStar(grid, came_from, cost_so_far);
        std::vector<Node> path = reconstructPath(grid, came_from);
        clock_t stop = clock();
        double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
        printf("\nTime elapsed: %.5f\n", elapsed);
        printPath(path);
        executionTimes.push_back(elapsed);
    }

    double sumOfExecTimes = std::accumulate(executionTimes.begin(), executionTimes.end(), 0.0000);
    double avgExecTime = sumOfExecTimes / executionTimes.size();
    std::cout << avgExecTime;
}
