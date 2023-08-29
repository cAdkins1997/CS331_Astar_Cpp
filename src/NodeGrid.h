#pragma once
#include <cmath>

#include "Node.h"

class NodeGrid
{
private:
    Node nodeGrid[10][10];
    Node targetNode;
    
public:
    NodeGrid()
    {
        int idInc = 0;
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                idInc++;
                nodeGrid[i][j].set_type(0);
                nodeGrid[i][j].set_x_location(i);
                nodeGrid[i][j].set_y_location(j);
                nodeGrid[i][j].set_id(idInc);
            }
        }

        initTargetNode();
    }

    void initTargetNode()
    {
        int xValue = rand() % 10 + 1;
        int yValue = rand() % 10 + 1;

        nodeGrid[xValue][yValue].set_type(2);
        targetNode = nodeGrid[xValue][yValue];
    }
};
