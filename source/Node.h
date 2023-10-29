
#ifndef ASTARSHORTESTPATH_NODE_H
#define ASTARSHORTESTPATH_NODE_H

enum nodeType {
    normal = 0,
    obstacle = 1,
    target = 2,
    start = 4,
    pathNode = 5
};

class Node {

public:

    Node() = default;

    [[nodiscard]] int getId() const {
        return id;
    }

    void setId(int _id) {
        Node::id = _id;
    }

    [[nodiscard]] int getXLocation() const {
        return xLocation;
    }

    void setXLocation(int _xLocation) {
        Node::xLocation = _xLocation;
    }

    [[nodiscard]] int getYLocation() const {
        return yLocation;
    }

    void setYLocation(int _yLocation) {
        Node::yLocation = _yLocation;
    }

    void setLocation(int _x, int _y) {
        this->xLocation = _x;
        this->yLocation = _y;
    }

    [[nodiscard]] nodeType getType() const {
        return type;
    }

    void setType(nodeType _type) {
        Node::type = _type;
    }

    [[nodiscard]] double getGCost() const {
        return g_cost;
    }

    void setGCost(double gCost) {
        g_cost = gCost;
    }

    [[nodiscard]] double getHCost() const {
        return h_cost;
    }

    void setHCost(double hCost) {
        h_cost = hCost;
    }

    [[nodiscard]] double getFCost() const {
        return f_cost;
    }

    void setFCost(double fCost) {
        f_cost = fCost;
    }

private:
    int id{};
    int xLocation{};
    int yLocation{};
    nodeType type = normal;

    double g_cost = 0;
    double h_cost = 0;
    double f_cost = 0;
};

inline bool isFCostLesser(const Node& node1, const Node& node2) {
    return node1.getFCost() < node2.getFCost();
}

inline bool operator==(Node *firstNode, const Node& secondNode) {
    return secondNode.getId() == firstNode->getId();
}

inline bool operator==(const Node& firstNode, const Node& secondNode) {
    return secondNode.getId() == firstNode.getId();
}

inline bool operator!=(const Node& firstNode, const Node& secondNode)
{
    return secondNode.getId() != firstNode.getId();
}

inline bool operator<(const Node& firstNode, const Node& secondNode) {
    return secondNode.getFCost() < firstNode.getFCost();
}

inline bool operator>(const Node& firstNode, const Node& secondNode) {
    return secondNode.getFCost() > firstNode.getFCost();
}

inline int calcDistanceDiagonal(const Node& currentNode, const Node& comparedNode) {
    int currentX = currentNode.getXLocation();
    int currentY = currentNode.getYLocation();

    int comparedX = comparedNode.getXLocation();
    int comparedY = comparedNode.getYLocation();

    int distanceX = abs(currentX - currentY);
    int distanceY = abs(currentX - currentY);

    double d1 = 3;
    double d2 = 4;

    return d1 * (distanceX + distanceY) + (d2 - 2 * d1) * std::min(distanceX, distanceY);
}

inline double calcDistanceEuclidean(const Node& currentNode, const Node& comparedNode) {
    int currentX = currentNode.getXLocation();
    int currentY = currentNode.getYLocation();

    int comparedX = comparedNode.getXLocation();
    int comparedY = comparedNode.getYLocation();

    return sqrt(pow(comparedX - currentX, 2) + pow(comparedY - currentY, 2));
}

inline int calcDistanceManhattan(const Node& firstNode, const Node& secondNode) {
    int dx = abs(firstNode.getXLocation() - secondNode.getXLocation());
    int dy = abs(firstNode.getYLocation() - secondNode.getYLocation());
    int d = 3;
    return d * (dx + dy);
}

#endif //ASTARSHORTESTPATH_NODE_H