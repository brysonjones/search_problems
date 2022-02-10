
#include "simulator.hpp"

// Member functions definitions including constructor
Simulator::Simulator() {
    
}

int Simulator::setup(std::vector<int> map_size) {
    // create robot
    robot.setup(0, 0, map_size, GREEN);

    visualizer.setup(robot);

    return 0;

}

int Simulator::moveRobot(){
    visualizer.renderRobot(robot.state[0], robot.state[1], 0);
}
