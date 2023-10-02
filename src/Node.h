
#ifndef ASTARSHORTESTPATH_NODE_H
#define ASTARSHORTESTPATH_NODE_H

#include <limits>

enum nodeType {
    normal = 0,
    start = 1,
    target = 2,
    obstacle = 4,
    pathNode = 5
};

class Node {

public:

    Node() = default;

    Node(int _id, int _xLocation, int _yLocation) {
        id = _id;
        xLocation = _xLocation;
        yLocation = _yLocation;
        visited = false;
    }

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

    [[nodiscard]] Node *getParent() const {
        return parent;
    }

    void setParent(Node *_parent) {
        Node::parent = _parent;
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

    [[nodiscard]] bool isVisited() const {
        return visited;
    }

    void setVisited(bool _visited) {
        Node::visited = _visited;
    }

private:
    int id{};
    int xLocation{};
    int yLocation{};
    bool visited{};
    Node* parent = nullptr;
    nodeType type = normal;

    double g_cost = std::numeric_limits<double>::infinity();
    double h_cost = std::numeric_limits<double>::infinity();;
    double f_cost = std::numeric_limits<double>::infinity();;
};

inline bool isFCostLesser(const Node& node1, const Node& node2) {
    return node1.getFCost() < node2.getFCost();
}

inline bool operator==(Node *firstNode, const Node& secondNode) {
    return secondNode.getId() == firstNode->getId();
}

inline bool operator==(Node firstNode, const Node secondNode) {
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

inline double calcDistanceEuclidean(const Node& currentNode, const Node& comparedNode) {
    int currentX = currentNode.getXLocation();
    int currentY = currentNode.getYLocation();

    int comparedX = comparedNode.getXLocation();
    int comparedY = comparedNode.getYLocation();

    return sqrt(((currentX - comparedX) * 2) + ((currentY - comparedY) * 2));
}

inline int calcDistanceManhattan(const Node& firstNode, const Node& secondNode) {
    double dx = abs(firstNode.getXLocation() - secondNode.getXLocation());
    double dy = abs(firstNode.getYLocation() - secondNode.getYLocation());
    double d = 3.0;
    return d * (dx + dy);
}

#endif //ASTARSHORTESTPATH_NODE_H