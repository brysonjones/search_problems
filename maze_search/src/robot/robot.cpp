
#include "robot.hpp"

// Member functions definitions including constructor
Robot::Robot() {}

int Robot::setup(int initialX, int initialY, std::vector<int> map_size, int color) {
    state[0] = initialX;
    state[1] = initialY;

    std::vector<float> xOffset = {(float)size/map_size[0], -(float)size/map_size[0], (float)size/map_size[0], -(float)size/map_size[0]}; // TODO: Convert this to robot size attribute
    std::vector<float> yOffset = {-(float)size/map_size[1], -(float)size/map_size[1], (float)size/map_size[1], (float)size/map_size[1]};

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
