//
// Created by Stephan on 18.05.2022.
//
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "mygraph.h"
#include "MyString.h"
#include "KGetLine.h"
#include "Errors.h"

Vertex * vertex_init(char * info) {
    Vertex * vertex = malloc(sizeof(Vertex));
    if (vertex == NULL) {
        fprintf(stderr, "memory not enough for new vertex.\n");
        exit(MEMORY_OVERFLOW);
    }

    vertex->in_list = adj_list_init(NULL, 0);
    vertex->out_list = adj_list_init(NULL, 0);
    vertex->info = info;

    vertex->free = vertex_free;
    vertex->add_edge = vertex_add_edge;

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

    free(vertex->info);
    free(vertex);

    return IT_IS_OK;
}

Vertex * vertex_enter() {
    char * line = NULL;
    do {
        if (line)
            free(line);
        line = get_line();
    } while (line == NULL || line[0] == '\0');

    Vertex * vertex = vertex_init(line);

    return vertex;
}

Error vertex_add_edge(Vertex * vertex, Edge * edge) {
    if (vertex == NULL) {
        fprintf(stderr, "null vertex in adding edge to it.\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }
    if (edge == NULL) {
        fprintf(stderr, "null edge in adding it to vertex.\n");
    }

    if (!strcmp(vertex->info, edge->v1->info)) {
        if (edge->orientation == V1_to_V2) {
            vertex->out_list->add(vertex->out_list, edge->v2, edge->weight);
        } else {
            vertex->in_list->add(vertex->in_list, edge->v2, edge->weight);
        }
    }
    else if (!strcmp(vertex->info, edge->v2->info)) {
        if (edge->orientation == V1_to_V2) {
            vertex->in_list->add(vertex->in_list, edge->v1, edge->weight);
        } else {
            vertex->out_list->add(vertex->out_list, edge->v1, edge->weight);
        }
    } else {
        fprintf(stderr, "there is not current vertex in edge.\n");
        return RUNTIME_ERROR;
    }

    return IT_IS_OK;
}