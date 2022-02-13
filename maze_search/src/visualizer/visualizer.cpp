
#include "visualizer.hpp"

// Member functions definitions including constructor
Visualizer::Visualizer() {
}

int Visualizer::setup(Robot robot, std::vector<int> map_bounds) {
    
    // glfw window creation
    if (window.setup()){
        return 1;
    }
    shader.setup();

    line.setup();

    _map_bounds = map_bounds;

    // set up shader object
    initObject(robot.vertices, sizeof(robot.vertices),
               robot.indices, sizeof(robot.indices), robotShaderIndex);
    
    return 0;

}

int Visualizer::initObject(float vertices[], int verticesSize, 
                           unsigned int indices[], int indicesSize, int shaderIndex){
    shader.setup_shader_program(vertices, verticesSize, indices, indicesSize, shaderIndex);
}

int Visualizer::processRenderEvents(){
    return window.render_loop();
}

int Visualizer::renderRobot(int x, int y, float theta){
    float xNormal = ((float)x) / (window.WINDOW_WIDTH / 2); // TODO: change this to map size variable
    float yNormal = ((float)y) / (window.WINDOW_HEIGHT / 2); // TODO: change this to map size variable
    bindVertex(robotShaderIndex);
    graphics::transform_2D(xNormal, yNormal, theta, shader.ID); // TODO: shader.ID should not be public here
}

int Visualizer::renderPath(const std::deque<std::vector<int>> &path){
    std::vector<float> pathRenderingVec;
    for (int i=0; i<path.size(); i++){
        const std::vector<int> *state = &path[i];
        pathRenderingVec.push_back((float)state->at(0) / ((_map_bounds[1] - _map_bounds[0])/2));
        pathRenderingVec.push_back((float)state->at(1) / ((_map_bounds[3] - _map_bounds[2])/2));
        pathRenderingVec.push_back(0.0f);
    }
    line.updatePos(pathRenderingVec);
    glm::mat4 tmpTransform = glm::mat4(1.0f);
    std::vector<glm::mat4> transformVector;
    transformVector.push_back(tmpTransform);
    line.updateTransform(transformVector);
    line.draw();
}

void Visualizer::bindVertex(int index){
    glBindVertexArray(shader.VAO_vec[index]);
    shader.use();
}

void Visualizer::cleanUpResources(){
    
    // de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    while(shader.VAO_vec.size() > 0){
        shader.delete_vertex_array(0);
    }

    line.~Line();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
}
