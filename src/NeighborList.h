#pragma once
#include "NodeGrid.h"

inline void fillNeighborArray(const NodeGrid& node_grid, std::vector<Node>& neighborArray)
{
    const Node location = node_grid.getLocationNode();
        
    int locationX = location.x_location() - 1;
    int locationY = location.y_location() - 1;

    int xBound = locationX + 3;
    int yBound = locationY + 3;
    xBound = clamp(xBound, 0, 9);
    yBound = clamp(yBound, 0, 9);
    
    for (int i = locationX; i < xBound; i++)
    {
        locationX++;
        for (int j = locationY; j < yBound; j++)
        {
            Node currentNode = node_grid.getNode(i, j);
            if (i >= 0 && j >= 0 && i < 10 && j < 10 && currentNode != location)
            {
                neighborArray.push_back(currentNode);
            }
        }
    }
}

inline void generateNeighborCosts(std::vector<Node>& neighborArray, const NodeGrid& node_grid)
{
    Node location = node_grid.getLocationNode();
    Node target = node_grid.get_TargetNode();
    
    for (auto& i : neighborArray)
    {
        i.calcGCost(location);
        i.calcHCost(target);
        i.calcFCost();
    }
}

inline std::vector<Node> createNeighborArray(const NodeGrid& node_grid, std::vector<Node>& neighborArray)
{
    fillNeighborArray(node_grid, neighborArray);
    generateNeighborCosts(neighborArray, node_grid);
    std::sort(neighborArray.begin(), neighborArray.end(), isFCostLesser);
    return neighborArray;
}