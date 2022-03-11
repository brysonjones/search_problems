#pragma once

#include<limits.h> 
#include <deque>
#include <queue>     
#include <unordered_map>
#include <vector>      
#include <functional>  
#include <utility>
#include <stack>
#include <chrono>
#include <math.h>
#include <iostream>
#include <memory.h>

#include "environment/environment.hpp"

namespace aStar {

static int MAX_COST = INT_MAX;

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
                  std::vector<int> map_bounds, std::vector<Obstacle> *obstacles);
        int search();

        int resetSearch();

        void computePath();

        void backTracePath();

        // motion directions
        int NUMOFDIRS = 8;
        int dX[8] = {-1, -1, -1,  0,  0,  1, 1, 1};
        int dY[8] = {-1,  0,  1, -1,  1, -1, 0, 1};

        // map variables
        std::vector<int> x_bounds;
        std::vector<int> y_bounds;
        int cost = 1;

        std::vector<int> current_state;
        std::vector<int> goal_state;

        // init stack for storing path
        std::deque<std::vector<int>> path;


    private:
        bool isStateValid(Node state);
        int updateMap();
        bool isStateObstacle(Node state);
        bool isGoalExpanded();
        int getH(Node state);
        int getG(std::vector<int> &state);
        Node popOpenList();
        void insertIntoOpenList(Node &current_state, Node &state_prime);

        std::vector<Obstacle> *_obstacles;
        int map[1000][1000] = {0};
        std::unordered_map<std::vector<int>, Node, VectorHasher> closed_list;
        std::priority_queue<Node, std::vector<Node>, LessThanByF> open_list;
        std::unordered_map<std::vector<int>, Node, VectorHasher> open_list_map;

};
 
