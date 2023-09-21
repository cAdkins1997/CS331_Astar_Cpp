
#include <iostream>
#include <vector>
#include <algorithm>

#include "NeighborList.h"

Node aStar(NodeGrid& nodeGrid);

int main() {
    NodeGrid nodeGrid = NodeGrid();
    Node targetNode = nodeGrid.get_TargetNode();

    if (aStar(nodeGrid) == targetNode) {
        std::cout << "You found the node!!";
    }
}


//TODO working recursively, also implement non-recursive method (Probably better performance)
//TODO edge case where nodes get trapped going back and forth between the same route, find a fix for this
//TODO obstacle generation and handling
Node aStar(NodeGrid& nodeGrid) {
    Node targetNode = nodeGrid.get_TargetNode();

    std::vector<Node> nodesToEvaluate;
    createNeighborArray(nodeGrid, nodesToEvaluate);
    std::vector<Node> nodesEvaluated(10);
    const Node nextNode = nodesToEvaluate[0];
    nodeGrid.set_LocationNode(nextNode.x_location(), nextNode.y_location());
    nodesEvaluated.push_back(nextNode);
    if (nextNode == targetNode) {
        return nextNode;
    }
    return aStar(nodeGrid);
}