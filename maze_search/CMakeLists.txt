cmake_minimum_required(VERSION 3.0.0)
project (MotionPlanner)
set(CMAKE_BUILD_TYPE Release)

enable_testing()

# add_library(${PROJECT_NAME} "")

add_subdirectory(src)

add_executable(main src/main.cpp)

set_target_properties(main
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/Release"
)


