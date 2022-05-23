//
// Created by Stephan on 23.05.2022.
//
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"

#include "Errors.h"
#include "BFS.h"

El * E_init(Vertex * v, El * pr, El * next) {
    El * el = malloc(sizeof(El));
    el->next = next;
    el->pr = pr;
    el->v = v;
    el->color = WHITE;
    el->depth = -1;
    return el;
}

Error E_free(El * el) {
    if (el == NULL) {
        fprintf(stderr, "null el to free.\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }
    free(el);
    return IT_IS_OK;
}

Queue * Q_init() {
    Queue * Q = malloc(sizeof(Queue));
    Q->number_of_elements = 0;
    Q->tail = NULL;
    Q->hear = NULL;

    return Q;
}

Error Q_free(Queue * q) {
    if (q == NULL) {
        fprintf(stderr, "null queue to free\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }

    El * el = q->hear;
    while (el) {
        El * tmp = el->next;
        E_free(el);
        el = tmp;
    }
    free(q);

    return IT_IS_OK;
}

Error Q_add(Queue * q, El * el, Q_mode mode) {
    if (q == NULL) {
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }

    if (q->tail == NULL) {
        q->hear = el; // E_init(el, NULL, NULL);
        q->tail = q->hear;
    } else if (mode == TAIL) {
        q->tail->next = el;
        el->pr = q->tail; //E_init(v, q->tail, NULL);
        q->tail = q->tail->next;
    } else if (mode == HEAD) {
        el->next = q->hear;
        q->hear = el;// E_init(v, NULL, q->hear);
        q->hear->next->pr = q->hear;
    } else {
        return RUNTIME_ERROR;
    }
    q->number_of_elements++;

    return IT_IS_OK;
}

El * Q_pop(Queue * q, Q_mode mode) {
    if (q == NULL) {
        fprintf(stderr, "иди на.\n");
        return NULL;
    }

    if (q->hear == NULL) {
        fprintf(stderr, "null queue.\n");
        return NULL;
    }

    El * res = NULL;
    if (q->number_of_elements == 1) {
        res = q->hear;
        q->hear = q->hear->next;
        q->number_of_elements--;
        q->tail = NULL;
        res->next = NULL;
        res->pr = NULL;
        return res;
    }

    if (mode == HEAD) {
        res = q->hear;
        q->hear = q->hear->next;
        q->number_of_elements--;
        return res;
    } else if (mode == TAIL) {
        res = q->tail;
        q->tail = q->tail->pr;
        q->tail->next = NULL;
        res->next = NULL;
        res->pr = NULL;
        return res;
    }

    return NULL;
}

Vertex ** BFS(Graph * graph, Vertex * start_v, char * name, size_t * depth1) {
    if (graph == NULL || start_v == NULL || name == NULL) {
        return NULL;
    }

    El * all_v = malloc(graph->number_of_vertexes * sizeof(El));
    for (size_t i = 0; i < graph->number_of_vertexes; ++i) {
        all_v[i].next = NULL;
        all_v[i].pr = NULL;
        all_v[i].v = graph->vertexes + i;
        all_v[i].color = WHITE;
    }

    Queue * q = Q_init();
    size_t ind = _index(graph->vertexes, start_v);
    all_v[ind].depth = 0;
    Q_add(q, all_v + ind, TAIL);

    El ** tr = NULL;
    size_t number_of_v_in_tr = 0;

    Vertex * curr_v = NULL;
    size_t depth = 1;
    do {
        El * el = Q_pop(q, HEAD);
        curr_v = el->v;
        AdjacencyListEl * list_el = curr_v->out_list->head;
        ind = _index(graph->vertexes, curr_v);
        all_v[ind].color = BLACK;
        depth = all_v[ind].depth+1;
        for (size_t i = 0; i < curr_v->out_list->number_of_el; ++i) {
            ind = _index(graph->vertexes, list_el->vertex);
            if (all_v[ind].color == WHITE) {
                all_v[ind].color = GREY;
                all_v[ind].depth = depth;
                Q_add(q, all_v + ind, TAIL);
            }
            list_el = list_el->next;
        }
        tr = realloc(tr, sizeof(Vertex*) * (++number_of_v_in_tr));
        tr[number_of_v_in_tr-1] = all_v+_index(graph->vertexes, curr_v);
    } while (q->number_of_elements && strcmp(curr_v->info, name) != 0);
    if (q->number_of_elements == 0) {
        return NULL;
    }

    *depth1 = tr[number_of_v_in_tr-1]->depth;
    depth = *depth1;
    Vertex ** path = calloc(depth+1, sizeof(Vertex*));
    path[depth] = tr[number_of_v_in_tr-1]->v;
    for (size_t i = number_of_v_in_tr-2; i >= 0; ++i) {
        if (path[all_v[i].depth])
            continue;

        depth = all_v[i].depth;
        if (is_incidental(all_v[i].v, path[depth+1]->info)) {
            path[depth] = all_v[i].v;
        }
    }

    return path;
}