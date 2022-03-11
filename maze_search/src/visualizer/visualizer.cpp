
#include "visualizer.hpp"

// Member functions definitions including constructor
Visualizer::Visualizer() {}

int Visualizer::setup(Robot robot, std::vector<Obstacle> obstacles, std::vector<int> map_bounds) {
    // glfw window creation
    if (window.setup()){
        return 1;
    }
    robotShader.setup();
    std::vector<int> map_size = {map_bounds[1] - map_bounds[0],
                                 map_bounds[3] - map_bounds[2]};
    std::vector<float> robotVertices = graphics::generateVertices(robot.state, robot.dims, map_size, graphics::BLUE);

    robotShader.initShader(robotVertices, robotShaderIndex);

    obstacleShader.setup();
    std::vector<float> obstacleVertices = graphics::generateVertices(obstacles[0].state, obstacles[0].dims, map_size, graphics::RED);
    obstacleShader.initShader(obstacleVertices, obstacleShaderIndex);
    line.setup();

    _map_bounds = map_bounds;
    
    return 0;
}

int Visualizer::processRenderEvents(){
    return window.render_loop();
}

int Visualizer::renderRobot(int x, int y, float theta){
    // TODO: Try to move this normalization step to inside OpenGL tools library
    float xNormal = ((float)x) / ((_map_bounds[1] - _map_bounds[0])/2);  // TODO: change this to map size variable
    float yNormal = ((float)y) / ((_map_bounds[3] - _map_bounds[2])/2);  // TODO: change this to map size variable
    robotShader.bindVertex();
    robotShader.setTransform2D(xNormal, yNormal, theta);
    robotShader.draw();
}

int Visualizer::renderObstacles(int x, int y){
    // TODO: Try to move this normalization step to inside OpenGL tools library
    float xNormal = ((float)x) / ((_map_bounds[1] - _map_bounds[0])/2);  // TODO: change this to map size variable
    float yNormal = ((float)y) / ((_map_bounds[3] - _map_bounds[2])/2);  // TODO: change this to map size variable
    obstacleShader.bindVertex();
    obstacleShader.setTransform2D(xNormal, yNormal, 0);  // not capable of rotating right now due to mapping logic
    obstacleShader.draw();
}

int Visualizer::renderPath(const std::deque<std::vector<int>> &path){
    
    // take points in path and put them into single vector array for OpenGL context
    std::vector<float> pathRenderingVec;
    for (int i=0; i<path.size(); i++){
        const std::vector<int> *state = &path[i];
        pathRenderingVec.push_back((float)state->at(0) / ((_map_bounds[1] - _map_bounds[0])/2));
        pathRenderingVec.push_back((float)state->at(1) / ((_map_bounds[3] - _map_bounds[2])/2));
        pathRenderingVec.push_back(0.0f);
    }
    line.updatePos(pathRenderingVec);
    // transform here is an identity matrix, so no transform is applied
    glm::mat4 tmpTransform = glm::mat4(1.0f);
    std::vector<glm::mat4> transformVector;
    transformVector.push_back(tmpTransform);
    line.updateTransform(transformVector);
    line.setColor(glm::vec3(0,1,0));
    line.draw();
}

void Visualizer::cleanUpResources(){
    
    // de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    line.~Line();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
}
