
#ifndef ASTARSHORTESTPATH_NODEGRID_H
#define ASTARSHORTESTPATH_NODEGRID_H

#include <algorithm>
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

    void generateObstacles() {
        int obstacleNumberHorizontal = aStarRandom(0, 10);
        std::vector<int> horizontalObstacles;

        int obstacleNumberVertical = aStarRandom(0, 10);
        std::vector<int> verticalObstacles;

        int obstacleNumQuads = aStarRandom(0, 3);
        std::unordered_map<int, int> quadObstacles;

        for (int i = 0; i < obstacleNumberHorizontal; i++) {
            horizontalObstacles.push_back(aStarRandom(0, 5));
        }

        for (int i = 0; i < obstacleNumberVertical; i++) {
            verticalObstacles.push_back(aStarRandom(0, 5));
        }

        for (int i = 0; i < quadObstacles.size(); i++) {
            quadObstacles.emplace(aStarRandom(0, 4), aStarRandom(0, 4));
        }

        for (int horizontalObstacle : horizontalObstacles) {
            int ySelection = aStarRandom(0, 9);
            for (unsigned int j = 0; j < horizontalObstacle; j++) {
                nodeGrid[j][ySelection].setType(obstacle);
            }
        }

        for (int verticalObstacle : verticalObstacles) {
            int xSelection = aStarRandom(0, 9);
            for (int j = 0; j < verticalObstacle; j++) {
                nodeGrid[xSelection][j].setType(obstacle);
            }
        }

        for (auto quadObstacle : quadObstacles) {
            int xSelection = aStarRandom(0, 5);
            int ySelection = aStarRandom(0, 5);

            for (int x = 0; x < xSelection; x++) {
                for (int y = 0; y < ySelection; y++) {
                    nodeGrid[x][y].setType(obstacle);
                }
            }
        }
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

    std::vector<Node> reconstructPath(std::unordered_map<Node, Node>& came_from) {
        std::vector<Node> path;
        Node currentNode = targetNode;

        if (came_from.find(targetNode) == came_from.end()) {
            return path;
        }

        while (currentNode != startNode) {
            path.push_back(currentNode);
            nodeGrid[currentNode.getXLocation()][currentNode.getYLocation()].setType(pathNode);
            currentNode = came_from[currentNode];
        }
        path.push_back(startNode);
        std::reverse(path.begin(), path.end());

        return path;
    }

    void AStar(std::unordered_map<Node, Node>& came_from, std::unordered_map<Node, double>& cost_so_far) {

        PriorityQueue<Node, double> open;
        open.put(startNode, 0);

        came_from[startNode] = startNode;
        cost_so_far[startNode] = 0;

        while (!open.empty()) {
            Node currentNode = open.get();

            if (currentNode == targetNode) {
                break;
            }

            for (auto neighborNode : getNeighbors(currentNode)) {
                double new_cost = cost_so_far[currentNode] + calcDistanceManhattan(currentNode, neighborNode);

                if (cost_so_far.find(neighborNode) == cost_so_far.end()
                    || new_cost < cost_so_far[neighborNode]) {
                    cost_so_far[neighborNode];
                    double priority = new_cost + calcDistanceManhattan(neighborNode, targetNode);
                    open.put(neighborNode, priority);
                    came_from[neighborNode] = currentNode;
                }
            }
        }
    }

    void dijkstra_search(std::unordered_map<Node, Node>& came_from, std::unordered_map<Node, double>& cost_so_far) {
        PriorityQueue<Node, double> open;
        open.put(startNode, 0);

        came_from[startNode] = startNode;
        cost_so_far[startNode] = 0;

        while(!open.empty()) {
            Node currentNode = open.get();

            if (currentNode == targetNode) {
                std::cout << "Node found\n";
                break;
            }

            std::vector<Node> neighbors = getNeighbors(currentNode);
            for (auto neighborNode : neighbors) {
                double new_cost = cost_so_far[currentNode] + calcDistanceManhattan(currentNode, neighborNode);

                if (cost_so_far.find(neighborNode) == cost_so_far.end()
                    || new_cost < cost_so_far[neighborNode]) {
                    cost_so_far[neighborNode] = new_cost;
                    came_from[neighborNode] = currentNode;
                    open.put(neighborNode, new_cost);
                }
            }
        }
    }

    std::unordered_map<Node, Node> breadthFirstSearch() {
        std::queue<Node> open;
        open.push(startNode);

        std::unordered_map<Node, Node> came_from;
        came_from[startNode]  = startNode;

        int whileIterationNumber = 0;
        int forIterationNumber = 0;
        int nodePushNumber = 0;
        while (!open.empty()) {
            Node currentNode = open.front();
            open.pop();

            if (currentNode == targetNode) {
                break;
            }

            std::vector<Node> neighbors = getNeighbors(currentNode);
            for (auto neighborNode : neighbors) {
                forIterationNumber ++;
                if (came_from.find(neighborNode) == came_from.end()) {
                    nodePushNumber++;
                    open.push(neighborNode);
                    came_from[neighborNode] = currentNode;
                }
            }
        }

        return came_from;
    }

    void printGrid() {
        for (unsigned int y = 0; y < GRID_SIZE_Y; y++) {
            for (auto & x : nodeGrid) {
                std::cout << " [" << x[y].getXLocation() << "][" << x[y].getYLocation() << "] ";
            }
            std::cout << '\n';
        }
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
    }

private:
    Node nodeGrid[GRID_SIZE_X][GRID_SIZE_Y];
    Node startNode;
    Node targetNode;
};