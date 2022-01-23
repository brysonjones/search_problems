cmake_minimum_required(VERSION 3.15.0)
project (maze_search)
set (CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

include(FetchContent)
enable_testing()

# TODO: Break out all OpenGL related code into OpenGLTools repo for separately library
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

FetchContent_Declare(
  oglt_repo
  GIT_REPOSITORY https://github.com/brysonjones/open_gl_tools.git
  GIT_TAG        main
)
FetchContent_GetProperties(oglt_repo)
if(NOT oglt_repoo_POPULATED)
  # Fetch the content using previously declared details
  FetchContent_Populate(oglt_repo)
  add_subdirectory(${oglt_repo_SOURCE_DIR} ${oglt_repo_BINARY_DIR})
  include_directories(${oglt_repo_SOURCE_DIR}/src)
endif()

add_subdirectory(src)

add_executable(main src/main.cpp)

target_link_libraries(main 
                      robot
                      searchAlgorithm
                      glfw ${GLFW_LIBRARIES} 
                      OpenGL::GL 
                      ${CMAKE_DL_LIBS}
                      oglt::graphics oglt::shader oglt::window
                      glad_libs
                      glm::glm)

set_target_properties(main
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/Release"
)


