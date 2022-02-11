add_library(robot SHARED 
                  robot.cpp)

target_link_libraries(robot PUBLIC
                            searchAlgorithm)

target_include_directories(robot PUBLIC
                                  ${CMAKE_SOURCE_DIR}/src)           