
#include "robot.hpp"

// Member functions definitions including constructor
Robot::Robot() {}

int Robot::setup(int initialX, int initialY, std::vector<int> map_size, int color) {
    state.push_back(initialX);
    state.push_back(initialY);

    std::vector<float> xOffset = {(float)(size/2)/map_size[0], -(float)(size/2)/map_size[0], 
                                    (float)(size/2)/map_size[0], -(float)(size/2)/map_size[0]}; // TODO: Convert this to robot size attribute
    std::vector<float> yOffset = {-(float)(size/2)/map_size[1], -(float)(size/2)/map_size[1],   
                                    (float)(size/2)/map_size[1], (float)(size/2)/map_size[1]};

    // TODO: create general function for vertex generation, maybe in opengl tools library?
    for (int i=0; i<4; i++){
        vertices[0 + i*6] = state[0] + xOffset[i];
        vertices[1 + i*6] = state[1] + yOffset[i];
        if (color == RED){
            vertices[3 + i*6] = 1.0;
        }
        else if (color == GREEN){
            vertices[4 + i*6] = 1.0;
        }    
        else if (color == BLUE){
            vertices[5 + i*6] = 1.0;
        }

    }

}

int Robot::initPlanner(std::vector<int> goal_pose, std::vector<int> map_bounds){
    planner.setup(state, goal_pose, map_bounds);
    planner.main();
}

int Robot::updatePlan(){
    planner.updatePosition(state);
    planner.main();

    return 0;
}


const std::deque<std::vector<int>>* Robot::getPlan(){
    return planner.path;
}

int Robot::move(){
    state = planner.path->at(0);

    std::cout << "state: " << state[0] << ", " << state[1] << std::endl;
    planner.path->pop_front();

    return 0;
}
