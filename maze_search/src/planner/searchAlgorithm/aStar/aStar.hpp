#pragma once

#include<limits.h> 
#include <queue>     
#include <unordered_map>
#include <vector>      
#include <functional>  
#include <utility>
#include <stack>
#include <chrono>
#include <math.h>

namespace aStar {

struct Node
{
    std::vector<int> node_pose; // <x, y> position on map
    Node *parent; // parent node that this node expanded from
    int g = INT_MAX;
    int h = INT_MAX;
    int f = INT_MAX;
};

struct LessThanByF
{
    bool operator()(const Node& lhs, const Node& rhs) const
    {
        return lhs.f > rhs.f;
    }
};

// define custom hasing function for vector<int>
struct VectorHasher {
    int operator()(const std::vector<int> &V) const {
        int hash = V.size();
        for(auto &i : V) {
            hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

}

using namespace aStar;

class AStar {
    public:
        AStar();
        int setup(std::vector<int> robot_start_pose, std::vector<int> goal_pose, 
                 std::vector<std::vector<int>> &enviro_map);
        int search();
        int main();

        // motion directions
        int NUMOFDIRS = 8;
        int dX[8] = {-1, -1, -1,  0,  0,  1, 1, 1};
        int dY[8] = {-1,  0,  1, -1,  1, -1, 0, 1};

        // map variables
        int x_size = 0;
        int y_size = 0;
        int cost = 1;

    private:
        bool isStateValid(Node state);
        bool isGoalExpanded();
        int getHeuristic(Node state);
        std::stack<std::vector<int>> computePath();
    
        std::vector<int> initial_state;
        std::vector<int> goal_state;
        std::vector<std::vector<int>> *map;

        std::unordered_map<std::vector<int>, Node, VectorHasher> closed_list;
        std::priority_queue<Node, std::vector<Node>, LessThanByF> open_list;

        // init stack for storing path
        std::stack<std::vector<int>> path;

};
 
