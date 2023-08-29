
#include <iostream>
#include <vector>
#include <algorithm>

#include "Node.h"
#include "NodeGrid.h"

void printNodeVector(const std::vector<Node>& vector, const std::string& descriptionMessage);

int main() {
    NodeGrid node_grid;
    
    std::vector<Node> nodeToEvaluate(10);
    std::vector<Node> nodesEvaluated;

    Node areaNode[3][3];


    for (int i = 0; i < nodeToEvaluate.size(); i++) {
        nodeToEvaluate[i].set_id(i);
    }
    
    printNodeVector(nodeToEvaluate, "The list of nodes before being sorted by F_Values is: ");
    
    std::sort(nodeToEvaluate.begin(), nodeToEvaluate.end(), isFCostGreater);

    printNodeVector(nodeToEvaluate, "The list of nodes after being sorted by F_Values is: ");
    
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