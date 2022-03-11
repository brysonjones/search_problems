add_library(searchAlgorithm SHARED 
                            searchAlgorithm.cpp)

add_subdirectory(aStar)

target_link_libraries(searchAlgorithm PUBLIC
                                      aStar)

target_include_directories(searchAlgorithm PRIVATE ${PROJECT_SOURCE_DIR}/src)
