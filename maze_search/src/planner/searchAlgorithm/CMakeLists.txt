add_library(searchAlgorithm SHARED 
                            searchAlgorithm.cpp)

add_subdirectory(aStar)

target_link_libraries(searchAlgorithm PUBLIC
                                      aStar)
