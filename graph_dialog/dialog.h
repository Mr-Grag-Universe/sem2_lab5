//
// Created by Stephan on 18.04.2022.
//

#ifndef LAB4_PROT_DIALOG_H
#define LAB4_PROT_DIALOG_H
#include "Errors.h"

Error add_vertex_dialog(Graph * graph);
Error add_edge_dialog(Graph * graph);
Error delete_vertex_dialog(Graph * graph);
Error delete_edge_dialog(Graph * graph);
Error get_graph_dialog(const Graph *graph);
Error graph_print_as_lists(const Graph * graph);
Error graph_BFS_dialog(Graph * graph);
Error graph_BFA_dialog(Graph * graph);
Error graph_DFS_dialog(Graph * graph);
Error graph_top_sort_dialog(Graph * graph);
//Error timing_dialog();
//Error random_dialog(KD_tree ** tree);
//Error read_tree_dialog(KD_tree ** tree);
Error dialog_update_graphviz(Graph * graph);
Graph * read_graph();
#endif //LAB4_PROT_DIALOG_H
