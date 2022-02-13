#pragma once

#include <vector>

#include "aStar/aStar.hpp"


class Planner {
    public:
        Planner();
        int setup(std::vector<int> robot_pose, std::vector<int> goal_pose, std::vector<int> map_bounds);
        int search();
        int main();
        int updatePosition(std::vector<int> robot_pose);
        int updateGoal(std::vector<int> goal_state);

        std::deque<std::vector<int>> *path;

    private:
        AStar aStarSearch{};
        

};
 