
// external imports
#include <iostream>
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

    // render loop
    // -----------
    while(true){

        if (simulator.visualizer.processRenderEvents()){break;}

        // create transformations
        // float theta = 0.1*tan(glfwGetTime());
        simulator.robot.state[0] =  500*sin(glfwGetTime());
        simulator.robot.state[1] =  500*cos(glfwGetTime());
        simulator.moveRobot();
    }

    // clean up resources
    simulator.visualizer.cleanUpResources();

    return 0;
}