
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

    // ************ LINE TESTING
    glm::vec3 testPoint1 = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 testPoint2 = glm::vec3(1.0f,1.0f,0.0f);
    glm::mat4 transform[10];
    for(int i = 0; i < 10; i++)
    {
        glm::mat4 tmpTransform = glm::mat4(1.0f);
        transform[i] = glm::translate(tmpTransform, glm::vec3((float)i*0.05, 0.0f, 0.0f));
        std::cout << (float)i*0.05 << std::endl;
        transform[i] = tmpTransform;
    }  

    line.setup(testPoint1, testPoint2, transform);

    // for(unsigned int i = 0; i < 10; i++)
    // {
    //     line.setTransform(transform[i]);
    // }  
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
    graphics::transform_2D(xNormal, yNormal, theta, shader.ID);
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
