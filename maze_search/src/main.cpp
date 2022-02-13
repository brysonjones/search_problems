
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

        int dx_to_goal = abs(simulator.robot.state[0] - goal[0]);
        int dy_to_goal = abs(simulator.robot.state[1] - goal[1]);
                
        int dist_to_goal = sqrt((dx_to_goal * dx_to_goal) + (dy_to_goal * dy_to_goal));

        if (dist_to_goal < 10){
            goal[0] = -190;
            goal[0] = -420;
            simulator.robot.updateGoal(goal);
        }
    }

    // clean up resources
    simulator.visualizer.cleanUpResources();

    return 0;
}
