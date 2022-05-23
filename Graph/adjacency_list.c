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

AdjacencyListEl * adj_el_init(Vertex * vertex, AdjacencyListEl * next, int weight) {
    if (vertex == NULL) {
        fprintf(stderr, "NULL vertex in adj El init.\n");
    }
    AdjacencyListEl * el = malloc(sizeof(AdjacencyListEl));
    if (el == NULL) {
        fprintf(stderr, "memory not enough for init element.\n");
        exit(MEMORY_OVERFLOW);
    }

    vertex_copy(&(el->vertex), vertex);
    el->weight = weight;
    el->next = next;

    el->free = adj_el_free;

    return el;
}

Error adj_el_free(AdjacencyListEl * el) {
    if (el == NULL) {
        fprintf(stderr, "null El in freeing.\n");
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
    list->delete = adj_list_delete;
    list->print = adj_list_print;

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
    list->head = adj_el_init(vertex, tmp, weight);

    if (list->tail == NULL)
        list->tail = list->head;
    list->number_of_el++;

    return IT_IS_OK;
}

Error adj_list_delete(AdjacencyList * list, char * name) {
    if (list == NULL) {
        fprintf(stderr, "null list in deleting from adj list.\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }
    if (name == NULL) {
        fprintf(stderr, "null name in deleting from adj list.\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }
    if (list->head == NULL) {
        fprintf(stderr, "deleting from empty list.\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }

    AdjacencyListEl  * el = list->head;
    AdjacencyListEl * el_pr = list->head;

    while (el && el != list->tail && !strcmp(el->vertex.info, name)) {
        el_pr = el;
        el = el->next;
    }
    if (el == NULL) {
        fprintf(stderr, "there is not such element in this list.\n");
        return RUNTIME_ERROR;
    }
    list->number_of_el--;
    if (el == list->head) {
        el_pr = el->next;
        el->free(el);
        list->head = el_pr;
        if (el_pr == NULL)
            list->tail = NULL;
        return IT_IS_OK;
    }

    el_pr->next = el->next;
    el->free(el);

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

Error adj_list_print(AdjacencyList * list) {
    if (list == NULL) {
        fprintf(stderr, "null list in it's printing.\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }
    AdjacencyListEl * el = list->head;
    while (el) {
        printf("name: %s, weight: %d; ", el->vertex.info, el->weight);
        el = el->next;
    }
    if (list->number_of_el)
        printf("\n");

    return IT_IS_OK;
}