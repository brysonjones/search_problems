add_library(searchAlgorithm SHARED 
                            searchAlgorithm.cpp)

add_subdirectory(aStar)

target_link_libraries(searchAlgorithm PUBLIC
                                      aStar)

# target_sources(${PROJECT_NAME} 
#     PRIVATE 
#         ${CMAKE_CURRENT_SOURCE_DIR}/searchAlgorithm.cpp
#         ${CMAKE_CURRENT_SOURCE_DIR}/searchAlgorithm.hpp)

# add_subdirectory(aStar)