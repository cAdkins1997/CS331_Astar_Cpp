
#ifndef ASTARSHORTESTPATH_NODEGRID_H
#define ASTARSHORTESTPATH_NODEGRID_H

#include <algorithm>
#include "aStarUtility.h"

#define GRID_SIZE_X 100
#define GRID_SIZE_Y 100

#endif //ASTARSHORTESTPATH_NODEGRID_H

class NodeGrid {
public:
    NodeGrid() {
        int idInc = 0;
        for (int x = 0; x < GRID_SIZE_X; x++) {
            for (int y = 0; y < GRID_SIZE_Y; y++) {
                ++idInc;
                nodeGrid[x][y].setId(idInc);
                nodeGrid[x][y].setLocation(x, y);
            }
        }
        targetNode = getNode(aStarRandom(0, GRID_SIZE_X - 1), aStarRandom(0, GRID_SIZE_X - 1));
        startNode = getNode(aStarRandom(0, GRID_SIZE_X - 1), aStarRandom(0, GRID_SIZE_X - 1));
        while (startNode == targetNode) {
            startNode = getNode(aStarRandom(0, GRID_SIZE_X), aStarRandom(0, GRID_SIZE_X));
        }

        nodeGrid[targetNode.getXLocation()][targetNode.getYLocation()].setType(target);
        nodeGrid[startNode.getXLocation()][startNode.getYLocation()].setType(start);
    }

    inline std::vector<Node> getNeighbors(const Node& locationNode) {
        std::vector<Node> neighbors;

        int startX = locationNode.getXLocation() - 1;
        int startY = locationNode.getYLocation() - 1;

        int xBound = startX + 3;
        int yBound = startY + 3;
        xBound = clamp(xBound, 0, GRID_SIZE_X - 1);
        yBound = clamp(yBound, 0, GRID_SIZE_Y - 1);

        for (int i = startX; i < xBound; i++)
        {
            startX++;
            for (int j = startY; j < yBound; j++)
            {
                Node currentNode = nodeGrid[i][j];
                if (i >= 0 && j >= 0 && i < GRID_SIZE_X && j < GRID_SIZE_Y && currentNode != locationNode)
                {
                    neighbors.push_back(currentNode);
                }
            }
        }

        return neighbors;
    }

    [[nodiscard]] const Node& getNode(int x, int y) const {
        return nodeGrid[x][y];
    }

    [[nodiscard]] const Node& getStartNode() const {
        return startNode;
    }

    void setStartNode(const Node& _startNode) {
        NodeGrid::startNode = _startNode;
    }

    void setStartNode(int x, int y) {
        Node newStart;
        newStart.setLocation(x, y);
        newStart.setType(start);
        NodeGrid::startNode = newStart;
    }

    [[nodiscard]] const Node& getTargetNode() const {
        return targetNode;
    }

    void setTargetNode(int x, int y) {
        Node newTarget;
        newTarget.setLocation(x, y);
        newTarget.setType(start);
        NodeGrid::targetNode = newTarget;
    }

    void setTargetNode(const Node& _targetNode) {
        NodeGrid::targetNode = _targetNode;
    }

private:
    Node nodeGrid[GRID_SIZE_X][GRID_SIZE_Y];
    Node startNode;
    Node targetNode;
};