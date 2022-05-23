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

int * BFA(Graph * graph, Vertex * start_vertex) {
    if (graph == NULL) {
        fprintf(stderr, "null graph in BFA.\n");
        return NULL;
    }
    if (start_vertex == NULL) {
        fprintf(stderr, "null start vertex in BFA.\n");
        return NULL;
    }

    int * distance = calloc(graph->number_of_vertexes, sizeof(int));
    for (size_t i = 0; i < graph->number_of_vertexes; ++i) {
        if (graph->vertexes + i != start_vertex)
            distance[i] = 999999999;
    }

    size_t number_of_iterations = graph->number_of_vertexes-1;
    for (size_t i = 0; i < number_of_iterations; ++i) {
        for (size_t j = 0; j < graph->number_of_edges; ++j) {
            Edge * e = graph->edges[j];
            Vertex * u = (e->orientation == V1_to_V2) ? &(e->v1) : &(e->v2);
            Vertex * v = (e->orientation != V1_to_V2) ? &(e->v1) : &(e->v2);

            size_t ind1 = graph->get_vertex_index(graph, v->info);
            size_t ind2 = graph->get_vertex_index(graph, u->info);

            if (distance[ind1] > distance[ind2] + e->weight) {
                distance[ind1] = distance[ind2] + e->weight;
            }
        }
    }

    for (size_t i = 0; i < graph->number_of_edges; ++i) {
        Edge * e = graph->edges[i];
        Vertex * v = (e->orientation == V1_to_V2) ? &(e->v1) : &(e->v2);
        Vertex * u = (e->orientation != V1_to_V2) ? &(e->v1) : &(e->v2);

        size_t ind1 = graph->get_vertex_index(graph, v->info);
        size_t ind2 = graph->get_vertex_index(graph, u->info);

        if (distance[ind1] > distance[ind2] + e->weight) {
            free(distance);
            fprintf(stderr, "there is negative weighted circle.\n");
            return NULL;
        }
    }

    return distance;
}