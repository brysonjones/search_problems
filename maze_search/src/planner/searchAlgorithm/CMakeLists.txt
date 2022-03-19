add_library(searchAlgorithm SHARED 
                            searchAlgorithm.cpp)

add_subdirectory(aStar)

target_link_libraries(searchAlgorithm PUBLIC
                                      aStar
                                      nlohmann_json::nlohmann_json
                                      glm::glm)

target_include_directories(searchAlgorithm PRIVATE 
                                           ${PROJECT_SOURCE_DIR}/src 
                                           glm)
