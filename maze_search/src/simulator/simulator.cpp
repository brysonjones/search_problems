
#include "simulator.hpp"

// Member functions definitions including constructor
Simulator::Simulator() {
    
}

int Simulator::setup(std::vector<int> map_size, std::vector<int> map_bounds) {
    // create robot
    robot.setup(0, 0, map_size, BLUE);

    // init obstacles
    Obstacle obstacle;
    obstacle.pose[0] = 300;  // X location
    obstacle.pose[1] = 300;  // Y location
    obstacles.push_back(obstacle);

    visualizer.setup(robot, map_bounds);

    return 0;

}

int Simulator::moveRobot(){
    robot.move();
    robot.updatePlan();
    visualizer.renderRobot(robot.state[0], robot.state[1], 0);
    visualizer.renderPath(*robot.getPlan());
}

int Simulator::updateObstacles(){
    robot.move();
}