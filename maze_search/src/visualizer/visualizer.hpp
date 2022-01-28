#pragma once
#include <vector>

#include "shader/shader.hpp"
#include "window/window.hpp"
#include "graphics/graphics.hpp"

#include "robot/robot.hpp"

class Visualizer {
    public:
        Visualizer();

        int setup(Robot robot);
        int initObject(float vertices[], int verticesSize, unsigned int indices[], int indicesSize, int shaderIndex);
        int processRenderEvents();
        int renderRobot(int x, int y, float theta);
        void cleanUpResources();

        int robotShaderIndex = 0;
        int envShaderIndex = 1;

    private:
        Window window;
        Shader shader; 

        void bindVertex(int index);

};
 