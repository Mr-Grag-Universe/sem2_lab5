//
// Created by Stephan on 18.05.2022.
//
#include "stdlib.h"
#include "stdio.h"

#include "mygraph.h"
#include "MyString.h"
#include "KGetLine.h"
#include "Errors.h"

Vertex * vertex_init(char * info, AdjacencyList * in_list, AdjacencyList * out_list) {
    Vertex * vertex = malloc(sizeof(Vertex));
    if (vertex == NULL) {
        fprintf(stderr, "memory not enough for new vertex.\n");
        exit(MEMORY_OVERFLOW);
    }

    vertex->in_list = in_list;
    vertex->out_list = out_list;
    vertex->info = info;

    vertex->free = vertex_free;

    return vertex;
}

Error vertex_free(Vertex * vertex) {
    if (vertex == NULL) {
        fprintf(stderr, "null vertex in freeing.\n");
        return FREEING_OF_NULL_PTR;
    }

    if (vertex->in_list)
        vertex->in_list->free(vertex->in_list);
    if (vertex->out_list)
        vertex->out_list->free(vertex->out_list);

    free(vertex);

    return IT_IS_OK;
}