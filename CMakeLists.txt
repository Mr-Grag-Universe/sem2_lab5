cmake_minimum_required(VERSION 3.16)
project(lab5 C)

include_directories(libs libs/headers Graph)
add_subdirectory(libs)
add_subdirectory(Graph)

set(CMAKE_C_STANDARD 99)

add_executable(lab5 main.c)
target_link_libraries(lab5 mygraph)