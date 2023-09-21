#pragma once
#include <queue>
#include <stack>
#include <list>

#include "NeighborList.h"

inline std::list<Node> fillNodeList(const NodeGrid& node_grid);
inline Node findNextNode(const std::list<Node>& nodesToEvaluate, const std::vector<Node>& neighbors);

inline Node aStar(NodeGrid& node_grid, std::list<Node>& nodesToEvaluate, std::queue<Node>& evaluatedNodes)
{
    const Node target = node_grid.get_TargetNode();
    std::vector<Node> neighbors;
    createNeighborArray(node_grid, neighbors);
    Node nextNode = findNextNode(nodesToEvaluate, neighbors);
    
    node_grid.set_LocationNode(nextNode.x_location(), nextNode.y_location());
    evaluatedNodes.push(nextNode);
    nodesToEvaluate.remove(nextNode);

    if (nextNode == target)
    {
        std::cout << "Node has been found" << std::endl;
        return nextNode;
    }

    return aStar(node_grid, nodesToEvaluate, evaluatedNodes);
}

inline Node findNextNode(const std::list<Node>& nodesToEvaluate, const std::vector<Node>& neighbors)
{
    Node nextNode;
    auto it = std::find(nodesToEvaluate.begin(), nodesToEvaluate.end(), neighbors[0]);
    
    bool found = false;
    while (!found)
    {
        if (!(it == nodesToEvaluate.end()))
        {
            nextNode = neighbors[0];
            found = true;
        }
    }

    return nextNode;
}

inline std::list<Node> fillNodeList(const NodeGrid& node_grid)
{
    std::list<Node> nodeList;

    for (int i = 0; i < GRID_SIZE_X; i++)
    {
        for (int j = 0; j < GRID_SIZE_Y; j++)
        {
            nodeList.push_back(node_grid.getNode(i, j));
        }
    }

    return nodeList;
}
