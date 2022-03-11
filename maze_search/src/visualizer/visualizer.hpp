#pragma once
#include <vector>

#include "shader/shader.hpp"
#include "window/window.hpp"
#include "graphics/graphics.hpp"
#include "graphics/line.hpp"
#include "environment/environment.hpp"

#include "robot/robot.hpp"

class Visualizer {
    public:
        Visualizer();

        int setup(Robot robot, std::vector<Obstacle> obstacles, std::vector<int> map_bounds);
        int processRenderEvents();
        int renderRobot(int x, int y, float theta);
        int renderObstacles(int x, int y);
        int renderPath(const std::deque<std::vector<int>> &path);
        void cleanUpResources();

        int robotShaderIndex = 0;
        int obstacleShaderIndex = 0;
        int envShaderIndex = 1;      
        Line line;


    private:
        std::vector<int> _map_bounds;
        Window window;
        Shader robotShader; 
        Shader obstacleShader; 

};
 