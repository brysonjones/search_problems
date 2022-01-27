add_library(visualizer STATIC visualizer.cpp)

target_link_libraries(visualizer PUBLIC 
                                glfw ${GLFW_LIBRARIES} 
                                OpenGL::GL 
                                ${CMAKE_DL_LIBS}
                                glad_libs
                                oglt::graphics oglt::shader oglt::window
                                glm::glm)

target_include_directories(visualizer PUBLIC 
                       ${PROJECT_SOURCE_DIR}/src)
