//
// Created by Stephan on 24.05.2022.
//
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"

#include "Errors.h"
#include "MyMath.h"
#include "mygraph.h"

Vertex ** top_sort(Graph * graph) {
    if (graph == NULL) {
        fprintf(stderr, "graph is NULL in top-sort.\n");
        return NULL;
    }

    Vertex ** order = calloc(graph->number_of_vertexes, sizeof(Vertex*));

    return order;
}