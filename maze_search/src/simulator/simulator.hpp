#pragma once
#include <vector>

#include "robot/robot.hpp"
#include "visualizer/visualizer.hpp"

struct Obstacle
{
    std::vector<int> pose = {0, 0}; // <x, y> position on map
    int height = 100;
    int width = 100;
};

class Simulator {
    public:
        Simulator();
        int setup(std::vector<int> map_size, std::vector<int> map_bounds);
        int moveRobot();

        Robot robot{};
        Visualizer visualizer{};

    private:
        std::vector<Obstacle> obstacles;

};
 