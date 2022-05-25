//
// Created by Stephan on 24.05.2022.
//
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"

#include "Errors.h"
#include "MyMath.h"
#include "MyString.h"
#include "mygraph.h"
#include "binary_tree.h"

size_t hash(const char * name) {
    size_t hash = (size_t) name[0];
    for (size_t i = 1; i < strlen(name); ++i)
        hash ^= name[i];
    return hash;
}

size_t get_ind(Graph * graph, char * name, size_t ** indexes, size_t * ind_size) {
    size_t hash_v = hash(name);
    size_t old_hash = hash_v;
    while (strcmp(graph->vertexes[(*indexes)[hash_v]].info, name) != 0) {
        hash_v = (hash_v + 1) % *ind_size;
        if (old_hash == hash_v)
            break;
    }
    if (graph->number_of_vertexes+5 >= *ind_size) {
        *indexes = realloc(*indexes, sizeof(size_t) * (*ind_size * 2));
        for (size_t j = *ind_size; j < *ind_size * 2; ++j) {
            (*indexes)[j] = 0;
        }
        *ind_size *= 2;
    }
    return (*indexes)[hash_v];
}

void add_to_HT(Graph * graph, size_t ** indexes, char * name, size_t i, size_t * ind_size) {
    size_t hash_v = hash(graph->vertexes[i].info);
    size_t old_hash = hash_v;
    while ((*indexes)[hash_v] || strcmp(name, graph->vertexes[(*indexes)[hash_v]].info)) {
        hash_v = (hash_v + 1) % *ind_size;
        if (old_hash == hash_v)
            break;
//        if (*ind_size <= hash_v) {
//            size_t start = *ind_size;
//            *ind_size = (hash_v+1) * 2;
//            *indexes = realloc(*indexes, sizeof(size_t) * *ind_size);
//            for (size_t j = start; j < *ind_size; ++j)
//                (*indexes)[j] = 0;
//        }
    }
    (*indexes)[hash_v] = i;
    if (graph->number_of_vertexes+5 >= *ind_size) {
        *indexes = realloc(*indexes, sizeof(size_t) * (*ind_size * 2));
        for (size_t j = *ind_size; j < *ind_size * 2; ++j) {
            (*indexes)[j] = 0;
        }
        *ind_size *= 2;
    }
}

double * BFA(Graph * graph, Vertex * start_vertex) {
    if (graph == NULL) {
        fprintf(stderr, "null graph in BFA.\n");
        return NULL;
    }
    if (start_vertex == NULL) {
        fprintf(stderr, "null start vertex in BFA.\n");
        return NULL;
    }

    double * distance = calloc(graph->number_of_vertexes, sizeof(double));
    size_t ind_size = 50000;
    size_t * indexes = calloc(ind_size, sizeof(size_t));
    for (size_t i = 0; i < graph->number_of_vertexes; ++i) {
        if (graph->vertexes + i != start_vertex)
            distance[i] = 999999999;
        if (i+1 == graph->number_of_vertexes-1 || i % 100 == 0) {
            printf("end!!!");
        }
        add_to_HT(graph, &indexes, graph->vertexes[i].info, i, &ind_size);
    }

    size_t number_of_iterations = graph->number_of_vertexes-1;
    KeyType * key = init_key();
    for (size_t i = 0; i < number_of_iterations; ++i) {
        for (size_t j = 0; j < graph->number_of_edges; ++j) {
            Edge * e = graph->edges[j];
            Vertex * u = (e->orientation == V1_to_V2) ? &(e->v1) : &(e->v2);
            Vertex * v = (e->orientation != V1_to_V2) ? &(e->v1) : &(e->v2);

            size_t ind1 = get_ind(graph, v->info, &indexes, &ind_size); //graph->get_vertex_index(graph, v->info);
            size_t ind2 = get_ind(graph, u->info, &indexes, &ind_size); //graph->get_vertex_index(graph, u->info);

            if (distance[ind1] > distance[ind2] + e->weight) {
                distance[ind1] = distance[ind2] + e->weight;
            }
        }
    }

    for (size_t i = 0; i < graph->number_of_edges; ++i) {
        Edge * e = graph->edges[i];
        Vertex * v = (e->orientation == V1_to_V2) ? &(e->v1) : &(e->v2);
        Vertex * u = (e->orientation != V1_to_V2) ? &(e->v1) : &(e->v2);

        size_t ind1 = get_ind(graph, v->info, &indexes, &ind_size); //graph->get_vertex_index(graph, v->info);
        size_t ind2 = get_ind(graph, u->info, &indexes, &ind_size); //graph->get_vertex_index(graph, u->info);

        if (distance[ind1] > distance[ind2] + e->weight) {
            free(distance);
            fprintf(stderr, "there is negative weighted circle.\n");
            return NULL;
        }
    }

    return distance;
}