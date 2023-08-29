#pragma once
#include <cmath>
#include "Node.h"

class NodeGrid
{
private:

    struct locationStruct
    {
        int xPos;
        int yPos;

        locationStruct(int _xPos, int _yPos)
        {
            xPos = _xPos;
            yPos = _yPos;
        }
    };
    
    Node nodeGrid[10][10];
    Node& targetNode = nodeGrid[rand() % 10][rand() % 10];
    locationStruct locCord = initStartingNode();
    Node& locationNode = nodeGrid[locCord.xPos][locCord.yPos];
    
    locationStruct initStartingNode()
    {
        bool startFound = false;
        while (!startFound)
        {
            const int startX = rand() % 10;
            const int startY = rand() % 10;
            const int potentialStart[] = {startX, startY};
            const int target[] = {targetNode.x_location(), targetNode.y_location()};
            if (potentialStart != target)
            {
                nodeGrid[startX][startY].set_type(2);
                locationStruct coords = locationStruct(startX, startY);
                return coords;
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

        nodeGrid[targetNode.x_location()][targetNode.y_location()].set_type(1);
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
        const int currentX = locationNode.x_location();
        const int currentY = locationNode.y_location();
        nodeGrid[currentX][currentY].set_type(0);

        nodeGrid[x][y].set_type(2);
    }

    Node get_TargetNode() const
    {
        return targetNode;
    }
};
