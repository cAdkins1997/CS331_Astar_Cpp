
#include <iostream>
#include <vector>
#include <algorithm>

#include "AStar.h"

int main()
{
    NodeGrid nodeGrid = NodeGrid();
    std::list<Node> nodesToEvaluate = fillNodeList(nodeGrid);
    std::queue<Node> evaluatedNodes;
    
    aStar(nodeGrid, nodesToEvaluate, evaluatedNodes);
}