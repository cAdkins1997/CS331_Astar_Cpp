
#ifndef ASTARSHORTESTPATH_NODEGRID_H
#define ASTARSHORTESTPATH_NODEGRID_H

#include <algorithm>
#include <fstream>
#include <sstream>

#include "aStarUtility.h"

#define GRID_SIZE_X 10
#define GRID_SIZE_Y 10

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
        while (startNode == targetNode && targetNode.getType() != obstacle) {
            startNode = getNode(aStarRandom(0, GRID_SIZE_X), aStarRandom(0, GRID_SIZE_X));
        }

        std::vector<int> obstacles = readObstacleCSV("../resources/obstacles.csv");
        generateObstacles(obstacles);

        nodeGrid[targetNode.getXLocation()][targetNode.getYLocation()].setType(target);
        nodeGrid[startNode.getXLocation()][startNode.getYLocation()].setType(start);
    }

    std::vector<Node> reconstructPath(std::unordered_map<Node, Node>& parentChildPairs) {

        std::vector<Node> path;
        Node currentNode = targetNode;

        if (parentChildPairs.find(targetNode) == parentChildPairs.end()) {
            return path;
        }

        while (currentNode != startNode) {
            path.push_back(currentNode);
            if (currentNode != targetNode) {
                nodeGrid[currentNode.getXLocation()][currentNode.getYLocation()].setType(pathNode);
            }
            currentNode = parentChildPairs[currentNode];
        }
        path.push_back(startNode);
        std::reverse(path.begin(), path.end());

        return path;
    }

    inline std::vector<Node> getNeighbors(const Node& locationNode) {
        std::vector<Node> neighbors;

        int startX = locationNode.getXLocation() - 1;
        int startY = locationNode.getYLocation() - 1;

        int xBound = startX + 3;
        int yBound = startY + 3;
        xBound = std::clamp(xBound, 0, GRID_SIZE_X - 1);
        yBound = std::clamp(yBound, 0, GRID_SIZE_Y - 1);

        for (int i = startX; i < xBound; i++)
        {
            startX++;
            for (int j = startY; j < yBound; j++)
            {
                Node currentNode = nodeGrid[i][j];
                if (currentNode != locationNode)
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

    [[maybe_unused]] void setStartNode(const Node& _startNode) {
        this->startNode = _startNode;
    }

    [[maybe_unused]] void setStartNode(int x, int y) {
        Node newStart;
        newStart.setLocation(x, y);
        newStart.setType(start);
        this->startNode = newStart;
    }

    [[nodiscard]] const Node& getTargetNode() const {
        return targetNode;
    }

    [[maybe_unused]] void setTargetNode(int x, int y) {
        Node newTarget;
        newTarget.setLocation(x, y);
        newTarget.setType(start);
        this->targetNode = newTarget;
    }

    [[maybe_unused]] void setTargetNode(const Node& _targetNode) {
        this->targetNode = _targetNode;
    }

    void printGridTypes() {
        for (unsigned int y = 0; y < GRID_SIZE_Y; y++) {
            for (auto x : nodeGrid) {
                Node currentNode = x[y];
                std::cout << " [";
                if (currentNode.getType() == obstacle) {
                    std::cout << "0]";
                }
                else if (currentNode.getType() == start) {
                    std::cout << "S]";
                }
                else if (currentNode.getType() == target) {
                    std::cout << "T]";
                }
                else if (currentNode.getType() == pathNode) {
                    std::cout << "P]";
                }
                else {
                    std::cout << " ]";
                }
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }

private:
    Node nodeGrid[GRID_SIZE_X][GRID_SIZE_Y];
    Node startNode;
    Node targetNode;

    static std::vector<int> readObstacleCSV(const char *obstacleFilePath) {
        std::ifstream obstacleFile;
        std::string obstacleString;
        std::stringstream obstacleStream;
        std::vector<int> obstacles;

        obstacleFile.open(obstacleFilePath);
        obstacleStream << obstacleFile.rdbuf();
        obstacleFile.close();

        while (std::getline(obstacleStream, obstacleString, ',')) {
            int obstacle = std::stoi(obstacleString);
            obstacles.push_back(obstacle);
        }

        return obstacles;
    }

    void generateObstacles(std::vector<int>& obstacles) {
        int counter = 0;
        for (auto& x : nodeGrid) {
            for (auto& y : x) {
                int currentObstacle = obstacles[counter];
                auto obstacleData = static_cast<nodeType>(currentObstacle);
                y.setType(obstacleData);
                counter++;
            }
        }
    }
};