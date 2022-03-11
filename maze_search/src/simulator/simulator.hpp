#pragma once
#include <vector>

#include "robot/robot.hpp"
#include "visualizer/visualizer.hpp"
#include "environment/environment.hpp"

class Simulator {
    public:
        Simulator();
        int setup(std::vector<int> map_size, std::vector<int> map_bounds);
        int moveRobot();
        int updateObstacles();
        int updateMap();

        Robot robot{};
        std::vector<Obstacle> obstacles;
        Visualizer visualizer{};
        int map[1000][1000] = {0};

    private:
        std::vector<int> _map_bounds;

};
 