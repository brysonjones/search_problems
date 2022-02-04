
// external imports
#include <iostream>
#include <unistd.h>
#include "shader/shader.hpp"
#include "window/window.hpp"
#include "graphics/graphics.hpp"

// internal imports
#include "planner/searchAlgorithm/searchAlgorithm.hpp"
#include "simulator/simulator.hpp"

int main(int argc, char** argv)
{

    // init simulation
    Simulator simulator;
    simulator.setup();

    std::vector<std::vector<int>> window_map(1000, std::vector<int>(1000));
    std::vector<int> robot_pose {0, 0};
    std::vector<int> goal {500, 500};
    Planner planner;
    planner.setup(robot_pose, goal, window_map);
    planner.main();

    // render loop
    // -----------
    while(true){

        if (simulator.visualizer.processRenderEvents()) {break;}

        // create transformations
        if (!planner.path.empty()){
            std::vector<int> state = planner.path.at(0);
            planner.path.pop_front();
            simulator.robot.state[0] = state[0];
            simulator.robot.state[1] = state[1];
        }
        else {break;}
        sleep(0.01);
        simulator.moveRobot();
        simulator.visualizer.renderPath();
    }

    // clean up resources
    simulator.visualizer.cleanUpResources();

    return 0;
}
