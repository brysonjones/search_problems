#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "planner/searchAlgorithm/searchAlgorithm.hpp"
#include "environment/environment.hpp"

class Robot {
    public:
        Robot();
        int setup(std::vector<int> initial_state, std::vector<int> map_size, std::vector<Obstacle> *obstacles);
        int initPlanner(std::vector<int> goal_pose, std::vector<int> map_bounds);
        int updatePlan();
        int updateGoal(std::vector<int> goal);
        const std::deque<std::vector<int>>* getPlan();
        int move();

        std::vector<int> state;  // 3 values for (X, Y, Theta)
        std::vector<float> vertices;
        std::vector<int> dims = {80, 120};  // width, height
    private:
        Planner planner;
        std::vector<Obstacle> *_obstacles;
};
 