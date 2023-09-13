#pragma once
#include "Node.h"
#include "aStarUtility.h"

#define GRID_SIZE_X 10
#define GRID_SIZE_Y 10

class NodeGrid
{
private:
    Node nodeGrid[10][10];
    Node targetNode = nodeGrid[aStarRandom(0, GRID_SIZE_X)][aStarRandom(0, GRID_SIZE_Y)];
    Node startNode = nodeGrid[aStarRandom(0, GRID_SIZE_X)][aStarRandom(0, GRID_SIZE_X)];
    Node locationNode = startNode;
    
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
                nodeGrid[i][j].set_Location(i, j);
                nodeGrid[i][j].set_id(idInc);
            }
        }

        nodeGrid[targetNode.x_location()][targetNode.y_location()].set_type(1);
        targetNode = nodeGrid[aStarRandom(0, GRID_SIZE_X)][aStarRandom(0, GRID_SIZE_Y)];
        startNode = nodeGrid[aStarRandom(0, GRID_SIZE_X)][aStarRandom(0, GRID_SIZE_X)];
    }

    Node getLocationNode() const
    {
        return locationNode;
    }

    Node getStartNode() const
    {
        return locationNode;
    }

    void setLocationNode(int x, int y)
    {
        nodeGrid[x][y].set_Location(x, y);
        locationNode.set_Location(x, y);
    }

    void set_LocationNode(int x, int y)
    {
        const int currentX = locationNode.x_location();
        const int currentY = locationNode.y_location();
        nodeGrid[currentX][currentY].set_type(0);
        nodeGrid[x][y].set_type(2);
        Node location = nodeGrid[x][y];
        locationNode = location;
    }

    Node get_TargetNode() const
    {
        return targetNode;
    }
};
