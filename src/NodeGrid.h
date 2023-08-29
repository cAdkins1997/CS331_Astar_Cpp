#pragma once
#include <cmath>
#include "Node.h"

class NodeGrid
{
private:
    Node nodeGrid[10][10];
    Node targetNode;
    Node locationNode;

    void initTargetNode()
    {
        int targetX = rand() % 10;
        int targetY = rand() % 10;

        nodeGrid[targetX][targetY].set_type(1);
        targetNode = nodeGrid[targetX][targetY];
    }

    void initStartingNode()
    {
        bool startFound = false;
        while (!startFound)
        {
            int startX = rand() % 10;
            int startY = rand() % 10;
            int potentialStart[] = {startX, startY};
            int target[] = {targetNode.x_location(), targetNode.y_location()};
            if (potentialStart != target)
            {
                nodeGrid[startX][startY].set_type(2);
                locationNode = nodeGrid[startX][startY];
                startFound = true;
            }
        }
    }
    
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
        initStartingNode();
    }

    Node getLocationNode() const
    {
        for (unsigned int i = 0; i < 10; i++)
        {
            for (unsigned int j = 0; j < 10; j++)
            {
                if (nodeGrid[i][j].getType() == 2)
                {
                    return nodeGrid[i][j];
                }
            }
        }
    }

    void set_LocationNode(int x, int y)
    {
        int currentX = locationNode.x_location();
        int currentY = locationNode.y_location();
        nodeGrid[currentX][currentY].set_type(0);

        nodeGrid[x][y].set_type(2);
    }

    Node get_TargetNode() const
    {
        return targetNode;
    }
};
