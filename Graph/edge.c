//
// Created by Stephan on 20.05.2022.
//
#include "Errors.h"
#include "mygraph.h"
#include "KGetLine.h"
#include "MyString.h"

#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"

Edge * edge_init(Vertex v1, Vertex v2, Orientation orientation, int weight) {
    Edge * edge = malloc(sizeof(Edge));
    edge->orientation = orientation;
    vertex_copy(&(edge->v1), &v1);
    vertex_copy(&(edge->v2), &v2);
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

Edge * edge_enter(bool enter_weight) {
    printf("Enter your label1: ");
    char * v1_label = NULL;
    do {
        if (v1_label)
            free(v1_label);
        v1_label = get_line();
    } while (v1_label == NULL || v1_label[0] == '\0');

    printf("Enter your label2: ");
    char * v2_label = NULL;
    do {
        if (v2_label)
            free(v2_label);
        v2_label = get_line();
    } while (v2_label == NULL || v2_label[0] == '\0');

    Vertex v1 = vertex_init(v1_label);
    Vertex v2 = vertex_init(v2_label);

    Edge * edge = edge_init(v1, v2, V1_to_V2, 1);
    if (enter_weight) {
        int weight = get_int();
        edge->weight = weight;
    }

    return edge;
}