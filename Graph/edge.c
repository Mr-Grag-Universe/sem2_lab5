//
// Created by Stephan on 20.05.2022.
//
#include "Errors.h"
#include "mygraph.h"

#include "stdlib.h"
#include "stdio.h"

Edge * edge_init(Vertex * v1, Vertex * v2, Orientation orientation, int weight) {
    Edge * edge = malloc(sizeof(Edge));
    edge->orientation = orientation;
    edge->v1 = v1;
    edge->v2 = v2;
    edge->weight = weight;

    edge->free = edge_free;

    return edge;
}

Error edge_free(Edge * edge) {
    if (edge == NULL) {
        fprintf(stderr, "edge in null in freeing.\n");
        return FREEING_OF_NULL_PTR;
    }
    free(edge);
    return IT_IS_OK;
}
