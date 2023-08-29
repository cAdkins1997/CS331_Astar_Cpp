#pragma once

#include <vector>
#include "NodeGrid.h"


class NeighborArray
{
public:
    NeighborArray(const NodeGrid& nodeGrid)
    {
        Node nodeArea[3][3];
        fillNodeArea(nodeArea);
        Node location = nodeGrid.getLocationNode();
        boundsChecking(location, nodeArea);
        std::vector<Node> _neighborArray = fillNeighborArray(nodeArea);
        const Node loc = nodeGrid.getLocationNode();
        const Node target = nodeGrid.get_TargetNode();
        for (unsigned int i = 0; i < _neighborArray.size(); i++)
        {
            calcGCost(_neighborArray[i], location);
            calcHCost(_neighborArray[i], target);
            calcFCost(_neighborArray[i]);
        }
        neighborArray = _neighborArray;
    }

    std::vector<Node> getArray() const
    {
        return neighborArray;
    }

private:
    std::vector<Node> neighborArray;

    void fillNodeArea(Node (&nodeArea)[3][3])
    {
        int idInc = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                idInc++;
                nodeArea[i][j].set_x_location(i);
                nodeArea[i][j].set_y_location(j);
                nodeArea[i][j].set_id(idInc);
            }
        }
    }

    bool isValid(int x, int y)
    {
        return (y >= 0) && (y < 10) && (x >= 0) && (x < 10);
    }
    
    void boundsChecking(const Node& location, Node (&nodeArea)[3][3])
    {
        int locationX = location.x_location();
        int locationY = location.y_location();
        if (!isValid(locationX - 1, locationY))
        {
            for (unsigned int i = 0; i < 3; i++)
            {
                nodeArea[0][i].set_validity(false);
            }
        }
        if (!isValid(locationX + 1, locationY))
        {
            for (unsigned int i = 0; i < 3; i++)
            {
                nodeArea[2][i].set_validity(false);
            }
        }
        if (!isValid(locationX,locationY - 1))
        {
            for (unsigned int i = 0; i < 3; i++)
            {
                nodeArea[i][0].set_validity(false);
            }
        }
        if (!isValid(locationX, locationY + 1))
        {
            for (unsigned int i = 0; i < 3; i++)
            {
                nodeArea[i][2].set_validity(false);
            }
        }
    }
    
    std::vector<Node> fillNeighborArray(Node (&nodeArea)[3][3])
    {
        std::vector<Node> neighbor_array;
        
        for (unsigned int i = 0; i < 3; i++)
        {
            for (unsigned int j = 0; j < 3; j++)
            {
                if (nodeArea[i][j].get_validity() == true)
                {
                    neighbor_array.push_back(nodeArea[i][j]);
                }
            }
        }
    
        return neighbor_array;
    }
    
    /*void calcNeighborCosts(std::vector<Node>& array, const NodeGrid& nodeGrid)
    {
        const Node location = nodeGrid.getLocationNode();
        const Node target = nodeGrid.get_TargetNode();
        for (unsigned int i = 0; i < array.size(); i++)
        {
            calcGCost(array[i], location);
            calcHCost(array[i], target);
            calcFCost(array[i]);
        }
    }*/
};