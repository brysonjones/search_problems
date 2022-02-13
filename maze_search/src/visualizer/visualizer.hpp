#pragma once
#include <vector>

#include "shader/shader.hpp"
#include "window/window.hpp"
#include "graphics/graphics.hpp"
#include "graphics/line.hpp"

#include "robot/robot.hpp"

class Visualizer {
    public:
        Visualizer();

        int setup(Robot robot, std::vector<int> map_bounds);
        int initObject(float vertices[], int verticesSize, unsigned int indices[], int indicesSize, int shaderIndex);
        int processRenderEvents();
        int renderRobot(int x, int y, float theta);
        int renderPath(const std::deque<std::vector<int>> &path);
        void cleanUpResources();

        int robotShaderIndex = 0;
        int envShaderIndex = 1;      
        Line line;


    private:
        std::vector<int> _map_bounds;
        Window window;
        Shader shader; 

        void bindVertex(int index);

};
 