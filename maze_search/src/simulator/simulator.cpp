
#include "simulator.hpp"

// Member functions definitions including constructor
Simulator::Simulator() {}

int Simulator::setup(std::vector<int> map_size, std::vector<int> map_bounds) {
    _map_bounds = map_bounds;

    // init obstacles
    Obstacle obstacle;
    obstacle.state[0] = 150;  // X location
    obstacle.state[1] = 100;  // Y location
    obstacles.push_back(obstacle);

    // create robot
    robot.setup(0, 0, map_size, &obstacles);

    visualizer.setup(robot, obstacles, map_bounds);

    return 0;
}

int Simulator::moveRobot(){
    robot.move();
    robot.updatePlan();
    visualizer.renderRobot(robot.state[0], robot.state[1], 0);
    visualizer.renderPath(*robot.getPlan());
}

int Simulator::updateObstacles(){
    // obstacles are hard-coded to only have one instance right now
    // TODO: make modular to many obstacles
    // HACK: currently, the rendering is RELATIVE position, instead of ABSOLUTE
    //       Fix this in OpenGL tools
    obstacles[0].state[0] = 150;
    obstacles[0].state[1] = 100 + 250 * cos(glfwGetTime());
    visualizer.renderObstacles(obstacles[0].state[0] - 150, 
                               obstacles[0].state[1] - 100);
}

int Simulator::updateMap(){
    int x_loc;
    int y_loc;
    int width;
    int height;
    for (int i=0; i<obstacles.size(); i++){
        x_loc = obstacles[i].state[0];
        y_loc = obstacles[i].state[1];
        width = obstacles[i].dims[0];
        height = obstacles[i].dims[1];
        for (int obj_i=x_loc-width/2; obj_i<x_loc+width/2; obj_i++){
            for (int obj_j=y_loc-height/2; obj_j<y_loc+height/2; obj_j++){
                map[obj_i-_map_bounds[0]][obj_j-_map_bounds[2]] = INT_MAX; // TODO: Define as const?
            }
        }
    }
}