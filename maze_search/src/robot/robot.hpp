#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "planner/searchAlgorithm/searchAlgorithm.hpp"

enum ROBOT_COLORS {
    RED = 1,
    GREEN = 2,
    BLUE = 3
};

class Robot {
    public:
        Robot();
        int setup(int initialX, int initialY, std::vector<int> map_size, int color=RED); // "red", "green", "blue"
        int initPlanner(std::vector<int> goal_pose, std::vector<int> map_bounds);
        int updatePlan();
        int updateGoal(std::vector<int> goal);
        const std::deque<std::vector<int>>* getPlan();
        int move();

        std::vector<int> state;  // 1D, 2 values for (X, Y)
        std::vector<float> vertices;  // TODO: Make this initialization more modular
        std::vector<unsigned int> indices = {
            0, 1, 2, // first triangle
            1, 2, 3  // second triangle
        }; 
    private:
        Planner planner;
        int size = 100;

};
 