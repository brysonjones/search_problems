#pragma once
#include <vector>

#include "robot/robot.hpp"
#include "visualizer/visualizer.hpp"

class Simulator {
    public:
        Simulator();
        int setup();
        int moveRobot();

        Robot robot{};
        Visualizer visualizer{};

    private:

};
 