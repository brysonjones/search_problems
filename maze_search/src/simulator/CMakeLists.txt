add_library(simulator STATIC simulator.cpp)

target_link_libraries(simulator PUBLIC
                                robot
                                searchAlgorithm
                                visualizer)

target_include_directories(simulator PUBLIC 
                                     ${PROJECT_SOURCE_DIR}/src)
