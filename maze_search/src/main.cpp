
// external imports
#include <iostream>
#include <unistd.h>
#include "shader/shader.hpp"
#include "window/window.hpp"
#include "graphics/graphics.hpp"

// internal imports
#include "simulator/simulator.hpp"

int main(int argc, char** argv)
{

    // environment setup
    std::vector<int> map_size = {1000, 1000};
    std::vector<int> map_bounds = {-500, 500, -500, 500};
    std::vector<int> robot_pose {0, 0};
    std::vector<int> goal {190, 420};

    // init simulation
    Simulator simulator;
    simulator.setup(map_size, map_bounds);
    simulator.robot.initPlanner(goal, map_bounds);
    // render loop
    // -----------
    while(true){

        if (simulator.visualizer.processRenderEvents()) {break;}

        simulator.moveRobot();
    }

    // clean up resources
    simulator.visualizer.cleanUpResources();

    return 0;
}
