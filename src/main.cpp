
#include <iostream>
#include <vector>
#include <algorithm>

#include "NeighborArray.h"

void printNodeVector(const std::vector<Node>& vector, const std::string& descriptionMessage);

int main() {
    NodeGrid node_grid = NodeGrid();
    
    NeighborArray neighbor_array = NeighborArray(node_grid);
    std::vector<Node> nodesToEvaluate = neighbor_array.getArray();
    std::vector<Node> nodesEvaluated;
    
    std::sort(nodesToEvaluate.begin(), nodesToEvaluate.end(), isFCostGreater);
    
    Node current = nodesToEvaluate[0];

    nodesEvaluated.push_back(current);
    
    nodesToEvaluate.erase(nodesToEvaluate.begin());
}

void printNodeVector(const std::vector<Node>& vector, const std::string& descriptionMessage) {
    std::cout << descriptionMessage << std::endl;

    for (unsigned int i = 0; i < vector.size(); i++) {
        std::cout << "f_cost for Node: " << i << " is: " << vector[i].f_Cost() << std::endl;
    }

    std::cout << std::endl;
}