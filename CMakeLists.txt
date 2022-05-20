cmake_minimum_required(VERSION 3.16)
project(lab5 C)

include_directories(libs libs/headers Graph graph_dialog)
add_subdirectory(libs)
add_subdirectory(Graph)
add_subdirectory(graph_dialog)

set(CMAKE_C_STANDARD 99)

add_executable(lab5 main.c)

target_link_libraries(dialog mylib)
target_link_libraries(dialog mygraph)

target_link_libraries(mygraph mylib)

target_link_libraries(lab5 mygraph)
target_link_libraries(lab5 dialog)