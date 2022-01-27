
#include "simulator.hpp"

// Member functions definitions including constructor
Simulator::Simulator() {
    
}

int Simulator::setup() {
    // create robot
    robot.setup(0, 0, GREEN);

    visualizer.setup(robot);

    return 0;

}

int Simulator::moveRobot(){
    visualizer.renderRobot(robot.state[0], robot.state[1], 0);
}
