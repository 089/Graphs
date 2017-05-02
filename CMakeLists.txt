project(graphtool)

cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 14)

# Override output folder for conveniency.
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/graphtool")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/gui")
#add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/test")

