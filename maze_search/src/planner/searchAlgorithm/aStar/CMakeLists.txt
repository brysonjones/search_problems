
add_library(aStar SHARED 
                  aStar.cpp
                  motionPrim.cpp)

target_link_libraries(aStar PRIVATE
                            nlohmann_json::nlohmann_json
                            glm::glm)

target_include_directories(aStar PRIVATE 
                                 ${PROJECT_SOURCE_DIR}/src
                                 glm)
                                 