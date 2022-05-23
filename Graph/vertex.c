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

Vertex vertex_init(char * info) {
    Vertex vertex;

    vertex.in_list = adj_list_init(NULL, 0);
    vertex.out_list = adj_list_init(NULL, 0);
    vertex.info = info;

    vertex.free = vertex_free;
    vertex.add_edge = vertex_add_edge;
    vertex.delete_edge = vertex_delete_edge;
    vertex.print = vertex_print;

    return vertex;
}

Error vertex_free(Vertex vertex) {
    if (vertex.in_list)
        vertex.in_list->free(vertex.in_list);
    if (vertex.out_list)
        vertex.out_list->free(vertex.out_list);

    free(vertex.info);

    return IT_IS_OK;
}

Vertex vertex_enter() {
    char * line = NULL;
    do {
        if (line)
            free(line);
        line = get_line();
    } while (line == NULL || line[0] == '\0');

    Vertex vertex = vertex_init(line);

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

    if (!strcmp(vertex->info, edge->v1.info)) {
        if (edge->orientation == V1_to_V2) {
            vertex->out_list->add(vertex->out_list, &edge->v2, edge->weight);
        } else {
            vertex->in_list->add(vertex->in_list, &edge->v2, edge->weight);
        }
    }
    else if (!strcmp(vertex->info, edge->v2.info)) {
        if (edge->orientation == V1_to_V2) {
            vertex->in_list->add(vertex->in_list, &(edge->v1), edge->weight);
        } else {
            vertex->out_list->add(vertex->out_list, &(edge->v1), edge->weight);
        }
    } else {
        fprintf(stderr, "there is not current vertex in edge.\n");
        return RUNTIME_ERROR;
    }

    return IT_IS_OK;
}

Error vertex_delete_edge(Vertex * vertex, Edge * edge) {
    if (vertex == NULL) {
        fprintf(stderr, "null vertex in deleting edge to it.\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }
    if (edge == NULL) {
        fprintf(stderr, "null edge in deleting it to vertex.\n");
    }

    if (!strcmp(vertex->info, edge->v1.info)) {
        if (edge->orientation == V1_to_V2) {
            vertex->out_list->delete(vertex->out_list, edge->v2.info);
        } else {
            vertex->in_list->delete(vertex->in_list, edge->v2.info);
        }
    }
    else if (!strcmp(vertex->info, edge->v2.info)) {
        if (edge->orientation == V1_to_V2) {
            vertex->in_list->delete(vertex->in_list, edge->v1.info);
        } else {
            vertex->out_list->delete(vertex->out_list, edge->v1.info);
        }
    } else {
        fprintf(stderr, "there is not current vertex in edge.\n");
        return RUNTIME_ERROR;
    }

    return IT_IS_OK;
}

Error vertex_print(Vertex * v) {
    if (v == NULL) {
        printf("null\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }

    printf("vertex: %s\n", v->info);
    return IT_IS_OK;
}

bool is_incidental(Vertex * v1, char * name) {
    if (v1 == NULL || name == NULL)
        return 0;

    AdjacencyListEl * el = v1->out_list->head;
    for (size_t i = 0; i < v1->out_list->number_of_el; ++i) {
        if (!strcmp(el->vertex.info, name)) {
            return 1;
        }
        el = el->next;
    }

    return 0;
}

void vertex_copy(Vertex * v, Vertex * src) {
    if (v == NULL || src == NULL)
        return;
    memmove(v, src, sizeof(Vertex));
}