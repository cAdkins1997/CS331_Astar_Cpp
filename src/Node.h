#pragma once

class Node
{
private:
    enum type {free = 0, target = 1, location = 2, obstacle = 3};
    int id = 0;
    int xLocation = 0;
    int yLocation = 0;
    int type = 0;

    double g_cost = 0;
    double h_cost = 0;
    double f_cost = g_cost + h_cost;

    bool valid = true;
    
public:
    
    int calcManhattanDistance(const Node& comparedNode) const
    {
        const int targetX = comparedNode.xLocation;
        const int targetY = comparedNode.yLocation;
        
        return abs(xLocation - yLocation) + abs(targetX - targetY);
    }

    double calcEuclideanDistance(const Node& comparedNode) const
    {
        const int targetX = comparedNode.xLocation;
        const int targetY = comparedNode.yLocation;

        return sqrt(pow(targetX - xLocation, 2) + pow(targetY - yLocation, 2) * 1.0);
    }

    inline void calcGCost(const Node& locationNode)
    {
        set_g_cost(calcEuclideanDistance(locationNode));
    }

    inline void calcHCost(const Node& targetNode)
    {
        set_h_cost(calcEuclideanDistance(targetNode));
    }

    inline void calcFCost()
    {
        set_f_cost(g_cost + h_cost);
    }

    [[nodiscard]] int getId() const
    {
        return id;
    }

    [[nodiscard]] int x_location() const
    {
        return xLocation;
    }

    [[nodiscard]] int y_location() const
    {
        return yLocation;
    }

    [[nodiscard]] int getType() const
    {
        return type;
    }

    [[nodiscard]] double g_Cost() const
    {
        return g_cost;
    }

    [[nodiscard]] double h_Cost() const
    {
        return h_cost;
    }

    [[nodiscard]] double f_Cost() const
    {
        return f_cost;
    }

    void set_id(int _id)
    {
        this->id = _id;
    }

    void set_x_location(int x_location)
    {
        xLocation = x_location;
    }

    void set_y_location(int y_location)
    {
        yLocation = y_location;
    }

    void set_Location(int x, int y)
    {
        xLocation = x;
        yLocation = y;
    }

    void set_type(int _type)
    {
        this->type = _type;
    }

    void set_g_cost(double _g_cost)
    {
        this->g_cost = _g_cost;
    }

    void set_h_cost(double _h_cost)
    {
        this->h_cost = _h_cost;
    }

    void set_f_cost(double _f_cost)
    {
        this->f_cost = _f_cost;
    }

    [[nodiscard]] bool get_validity() const
    {
        return valid;
    }

    void set_validity(bool _valid)
    {
        this->valid = _valid;
    }
};

static inline bool isFCostGreater(const Node& node1, const Node& node2) {
    return node2.f_Cost() > node1.f_Cost();
}

inline bool operator==(const Node& firstNode, const Node& secondNode) {
    return secondNode.getId() == firstNode.getId();
}