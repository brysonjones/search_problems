#pragma once

#include <vector>

#include "aStar/aStar.hpp"


class Planner {
    public:
        Planner();
        int setup(std::vector<int> robot, std::vector<int> goal_pose, 
                  std::vector<std::vector<int>> &enviro_map);
        int search();
        int main();

    private:
        AStar aStarSearch{};

};
 