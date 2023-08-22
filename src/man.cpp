
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>


struct node {
    int id;

    int g_cost = rand() % 50 + 1;
    int h_cost = rand() % 50 + 1;
    int f_cost = g_cost + h_cost;

    friend bool operator==(const node& firstNode, const node& secondNode) {
        return secondNode.id == firstNode.id;
    }
};

node nodeGrid[10][10];

std::vector<node> nodesToEval(10);
std::vector<node> nodesEvaled;

void printNodeVector(const std::vector<node>& vector, const std::string& descriptionMessage);
bool isFCostGreater(const node& node1, const node& node2);

int main() {

    for (int i = 0; i < nodesToEval.size(); i++) {
        nodesToEval[i].id = i;
    }

    bool done = false;
    while (!done) {
        node targetNode;

        printNodeVector(nodesToEval, "The list of nodes before being sorted by F_Values is: ");

        std::sort(nodesToEval.begin(), nodesToEval.end(), isFCostGreater);
        printNodeVector(nodesToEval, "The list of nodes after being sorted by F_Values is: ");

        node current = nodesToEval[0];
        std::cout << current.g_cost;

        nodesToEval.erase(remove(nodesToEval.begin(), nodesToEval.end(), current), nodesToEval.end());

        nodesEvaled.push_back(current);

        done = true;
    }
}

void printNodeVector(const std::vector<node>& vector, const std::string& descriptionMessage) {
    std::cout << descriptionMessage << std::endl;

    for (int i = 0; i < vector.size(); i++) {
        std::cout << "f_cost for Node: " << i << " is: " << vector[i].f_cost << std::endl;
    }

    std::cout << std::endl;
}

bool isFCostGreater(const node& node1, const node& node2) {
    return node2.f_cost > node1.f_cost;
}