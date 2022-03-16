cmake_minimum_required(VERSION 3.15.0)
project (maze_search)
set (CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_POSITION_INDEPENDENT_CODE ON) # TODO: Change OGLT library to be Position Independent instead of this. This makes the code less efficient

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

include(FetchContent)
enable_testing()

# TODO: Break out all OpenGL related code into OpenGLTools repo for separately library
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

include(cmake/oglt.cmake)
include(cmake/json.cmake)

add_subdirectory(src)
include_directories(src)

add_executable(main src/main.cpp)

# HACK: Change the way this file gets placed 
#       Could generate it on build with the python script?
file(COPY src/motion_prim_gen/motion_prim.json
          DESTINATION ${CMAKE_BINARY_DIR}/bin/Release)

target_link_libraries(main
                      simulator)

set_target_properties(main
                      robot
                      searchAlgorithm
                      visualizer
                      simulator
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/Release"
)

install(TARGETS 
              main
              robot
              searchAlgorithm
              visualizer
              simulator
        ARCHIVE DESTINATION ARCHIVE_OUTPUT_DIRECTORY
        LIBRARY DESTINATION LIBRARY_OUTPUT_DIRECTORY
        RUNTIME DESTINATION RUNTIME_OUTPUT_DIRECTORY)

