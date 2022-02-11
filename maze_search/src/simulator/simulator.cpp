
#include "simulator.hpp"

// Member functions definitions including constructor
Simulator::Simulator() {
    
}

int Simulator::setup(std::vector<int> map_size, std::vector<int> map_bounds) {
    // create robot
    robot.setup(0, 0, map_size, GREEN);

    visualizer.setup(robot);

    return 0;

}

int Simulator::moveRobot(){
    robot.move();
    robot.updatePlan();
    visualizer.renderRobot(robot.state[0], robot.state[1], 0);
}
