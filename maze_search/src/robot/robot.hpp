#pragma once
#include <iostream>
#include <vector>
#include <string>

enum ROBOT_COLORS {
    RED = 1,
    GREEN = 2,
    BLUE = 3
};

class Robot {
    public:
        Robot();
        int setup(int initialX, int initialY, std::vector<int> map_size, int color=RED); // "red", "green", "blue"
        std::vector<int> state = {0}; // 1D, 2 values for (X, Y)
        float vertices[24] = {0}; // TODO: Make this initialization more modular
        unsigned int indices[6] = {
            0, 1, 2, // first triangle
            1, 2, 3  // second triangle
        }; 
    private:
        int size = 100;

};
 