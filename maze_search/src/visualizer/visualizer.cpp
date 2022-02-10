
#include "visualizer.hpp"

// Member functions definitions including constructor
Visualizer::Visualizer() {
}

int Visualizer::setup(Robot robot) {
    
    // glfw window creation
    if (window.setup()){
        return 1;
    }
    shader.setup();

    line.setup();

    // ************ LINE TESTING 

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
    float xNormal = ((float)x) / (window.WINDOW_WIDTH / 2);
    float yNormal = ((float)y) / (window.WINDOW_HEIGHT / 2);
    bindVertex(robotShaderIndex);
    graphics::transform_2D(xNormal, yNormal, theta, shader.ID); // TODO: shader.ID should not be public here
}

int Visualizer::renderPath(){
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
