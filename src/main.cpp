
#include <iostream>
#include <vector>
#include <algorithm>

#include "NeighborArray.h"

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