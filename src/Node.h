#pragma once


class Node
{
private:
    enum type {Free = 0, Obstacle = 1, Target = 2};
    int id = 0;
    int xLocation = 0;
    int yLocation = 0;
    int type = 0;

    int g_cost = rand() % 10 + 1;
    int h_cost = rand() % 10 + 1;
    int f_cost = g_cost + h_cost;
    
public:
    
    int calcManhattanDistance(const Node& targetNode) const
    {
        const int targetX = targetNode.xLocation;
        const int targetY = targetNode.yLocation;
        
        return abs(xLocation - yLocation) + abs(targetX - targetY);
    }

    int getId() const
    {
        return id;
    }

    int x_location() const
    {
        return xLocation;
    }

    int y_location() const
    {
        return yLocation;
    }

    int getType() const
    {
        return type;
    }

    int g_Cost() const
    {
        return g_cost;
    }

    int h_Cost() const
    {
        return h_cost;
    }

    int f_Cost() const
    {
        return f_cost;
    }

    void set_id(int id)
    {
        this->id = id;
    }

    void set_x_location(int x_location)
    {
        xLocation = x_location;
    }

    void set_y_location(int y_location)
    {
        yLocation = y_location;
    }

    void set_type(int type)
    {
        this->type = type;
    }

    void set_g_cost(int g_cost)
    {
        this->g_cost = g_cost;
    }

    void set_h_cost(int h_cost)
    {
        this->h_cost = h_cost;
    }

    void set_f_cost(int f_cost)
    {
        this->f_cost = f_cost;
    }
};

inline bool isFCostGreater(const Node& node1, const Node& node2) {
    return node2.f_Cost() > node1.f_Cost();
}

inline bool operator==(const Node& firstNode, const Node& secondNode) {
    return secondNode.getId() == firstNode.getId();
}