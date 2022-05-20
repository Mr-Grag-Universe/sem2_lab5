//
// Created by Stephan on 18.05.2022.
//
#include "stdlib.h"
#include "stdio.h"

#include "mygraph.h"
#include "MyString.h"
#include "KGetLine.h"
#include "Errors.h"

AdjacencyListEl * adj_el_init(Vertex * vertex, AdjacencyListEl * next, int weight) {
    if (vertex == NULL) {
        fprintf(stderr, "NULL vertex in adj el init.\n");
    }
    AdjacencyListEl * el = malloc(sizeof(AdjacencyListEl));
    if (el == NULL) {
        fprintf(stderr, "memory not enough for init element.\n");
        exit(MEMORY_OVERFLOW);
    }

    el->vertex = vertex;
    el->weight = weight;
    el->next = next;

    el->free = adj_el_free;

    return el;
}

Error adj_el_free(AdjacencyListEl * el) {
    if (el == NULL) {
        fprintf(stderr, "null el in freeing.\n");
        return FREEING_OF_NULL_PTR;
    }

    free(el);

    return IT_IS_OK;
}

AdjacencyList * adj_list_init(Vertex ** vertexes, size_t number_of_vertexes) {
    AdjacencyList * list = malloc(sizeof(AdjacencyList));
    if (list == NULL) {
        fprintf(stderr, "memory not enough for adj list init.\n");
        exit(MEMORY_OVERFLOW);
    }

    list->free = adj_list_free;
    list->add = adj_list_add;

    if (vertexes == NULL) {
        list->number_of_el = 0;
        list->tail = NULL;
        list->head = NULL;
        return list;
    }

    list->number_of_el = number_of_vertexes;
    for (size_t i = 0; i < number_of_vertexes; ++i) {
        if (vertexes[i] == NULL) {
            fprintf(stderr, "null ptr vertex in adj list init.\nadding has been stopped.\n");
            return list;
        }
        //add to list
    }

    return list;
}

Error adj_list_add(AdjacencyList * list, Vertex * vertex, int weight) {
    if (list == NULL) {
        fprintf(stderr, "null list in adding to adj list.\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }
    if (vertex == NULL) {
        fprintf(stderr, "null vertex in adding to adj list.\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }

    AdjacencyListEl * tmp = list->head;
    list->head = malloc(sizeof(AdjacencyListEl));
    list->head->next = tmp;

    if (list->tail == NULL)
        list->tail = list->head;
    list->number_of_el++;
    list->head->vertex = vertex;
    list->head->weight = weight;

    return IT_IS_OK;
}

Error adj_list_free(AdjacencyList * list) {
    if (list == NULL) {
        fprintf(stderr, "null adj list in freeing.\n");
        return FREEING_OF_NULL_PTR;
    }

    AdjacencyListEl * el = list->head;
    AdjacencyListEl * tmp = NULL;

    while (el) {
        tmp = el->next;
        el->free(el);
        el = tmp;
    }

    list->head = NULL;
    list->tail = NULL;

    free(list);

    return IT_IS_OK;
}