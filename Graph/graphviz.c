//
// Created by Stephan on 19.05.2022.
//
#include "stdio.h"

#include "Errors.h"
#include "mygraph.h"

Error print_graph(Graph * graph, FILE * stream) {
    if (graph == NULL) {
        fprintf(stderr, "null graph tried to be painted.\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }

    fprintf(stream, "digraph BST {\n");
    fprintf(stream, "    node [fontname=\"Arial\"];\n");

    for (size_t i = 0; i < graph->number_of_vertexes; ++i) {
        fprintf(stream, "\t%s;\n", graph->vertexes[i].info);
    }
    fprintf(stream, "\n");
    for (size_t i = 0; i < graph->number_of_edges; ++i) {
        if (graph->edges[i] == NULL) {
            fprintf(stderr, "null edge in graph.\n");
            return NULL_PTR_IN_UNEXCITED_PLACE;
        }
        Vertex * v1 = (graph->edges[i]->orientation == V1_to_V2) ? &graph->edges[i]->v1 : &graph->edges[i]->v2;
        Vertex * v2 = (graph->edges[i]->orientation == V1_to_V2) ? &graph->edges[i]->v2 : &graph->edges[i]->v1;
        fprintf(stream, "\t%s -> %s\n", v1->info, v2->info);
    }

    fprintf(stream, "}\n");

    return IT_IS_OK;
}