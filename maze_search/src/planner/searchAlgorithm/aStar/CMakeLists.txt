
add_library(aStar SHARED 
                  aStar.cpp)

message(${PROJECT_SOURCE_DIR}/src)
target_include_directories(aStar PRIVATE ${PROJECT_SOURCE_DIR}/src)
