project(graph_lib)

include_directories(binary_tree)
add_subdirectory(binary_tree)

add_library(mygraph graph.c vertex.c adjacency_list.c graphviz.c edge.c BFS_DFS.c BFS_DFS.h Bellman_Ford_algorithm.c DFS.c)