
#include <iostream>
#include <vector>
#include <algorithm>

#include "Node.h"
#include "NodeGrid.h"

void printNodeVector(const std::vector<Node>& vector, const std::string& descriptionMessage);

int main() {
    NodeGrid node_grid = NodeGrid();
    
    std::vector<Node> nodeToEvaluate;
    std::vector<Node> nodesEvaluated;

    Node location = node_grid.getLocationNode();
    
    std::sort(nodeToEvaluate.begin(), nodeToEvaluate.end(), isFCostGreater);
    
    Node current = nodeToEvaluate[0];
    std::cout << current.g_Cost();

    nodesEvaluated.push_back(current);
    
    nodeToEvaluate.erase(nodeToEvaluate.begin());
}

void printNodeVector(const std::vector<Node>& vector, const std::string& descriptionMessage) {
    std::cout << descriptionMessage << std::endl;

    for (int i = 0; i < vector.size(); i++) {
        std::cout << "f_cost for Node: " << i << " is: " << vector[i].f_Cost() << std::endl;
    }

    std::cout << std::endl;
}