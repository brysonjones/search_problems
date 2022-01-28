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
#include <iostream>

namespace aStar {

int MAX_COST = INT_MAX;

struct Node
{
    std::vector<int> node_pose = {0, 0}; // <x, y> position on map
    Node *parent = nullptr; // parent node that this node expanded from
    int g = MAX_COST;
    int h = MAX_COST;
    int f = MAX_COST;
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

        void computePath();

        void backTracePath();

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
        int getH(Node state);
        int getG(std::vector<int> &state);
        Node popOpenList();
        void insertIntoOpenList(Node &current_state, Node &state_prime);
    
        std::vector<int> initial_state;
        std::vector<int> goal_state;
        std::vector<std::vector<int>> *map;

        std::unordered_map<std::vector<int>, Node, VectorHasher> closed_list;
        std::priority_queue<Node, std::vector<Node>, LessThanByF> open_list;
        std::unordered_map<std::vector<int>, Node, VectorHasher> open_list_map;

        // init stack for storing path
        std::stack<std::vector<int>> path;

};
 
