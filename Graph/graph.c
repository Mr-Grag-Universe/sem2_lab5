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

Graph * graph_init(Vertex ** vertexes, Edge ** edges) {
    Graph * graph = malloc(sizeof(Graph));
    if (graph == NULL) {
        fprintf(stderr, "memory not enough for graph init.\n");
        exit(MEMORY_OVERFLOW);
    }

    graph->vertexes = NULL;
    graph->edges = NULL;
    graph->number_of_edges = 0;
    graph->number_of_vertexes = 0;

    graph->add_vertex = graph_add_vertex;
    graph->add_edge = graph_add_edge;
    graph->get_vertex = graph_get_vertex;
    graph->print = print_graph;

    return graph;
}

Error graph_add_few_vertexes(Vertex * vertex);
Error graph_add_vertex(Graph * graph, Vertex * vertex) {
    if (graph == NULL) {
        fprintf(stderr, "graph is NULL in adding.\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }
    if (vertex == NULL) {
        fprintf(stderr, "vertex is NULL in adding.\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }

    graph->vertexes = realloc(graph->vertexes, sizeof(Vertex) * (graph->number_of_vertexes + 1));
    graph->vertexes[graph->number_of_vertexes] = vertex;

    graph->number_of_vertexes++;

    return IT_IS_OK;
}

Error graph_add_few_edges(Edge * edge);
Error graph_add_edge(Graph * graph, Edge * edge) {
    if (graph == NULL) {
        fprintf(stderr, "graph is NULL in adding.\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }
    if (edge == NULL) {
        fprintf(stderr, "edge is NULL in adding.\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }
    if (edge->v1 == NULL || edge->v2 == NULL) {
        fprintf(stderr, "edge v1 or v2 is null in adding.\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }

    Vertex * v1 = graph->get_vertex(graph, edge->v1->info);
    if (v1 == NULL) {
        graph->add_vertex(graph, edge->v1);
        v1 = graph->get_vertex(graph, edge->v1->info);
    }
    Vertex * v2 = graph->get_vertex(graph, edge->v2->info);
    if (v2 == NULL) {
        graph->add_vertex(graph, edge->v2);
        v2 = graph->get_vertex(graph, edge->v2->info);
    }

    // проверяем что действительно добавили
    if (v1 == NULL || v2 == NULL) {
        fprintf(stderr, "Error!!! v1 or v2 was not added.\n");
        exit(RUNTIME_ERROR);
    }

    if (edge->orientation == V1_to_V2) {
        v1->out_list->add(v1->out_list, edge->v2, edge->weight);
        v2->in_list->add(v2->in_list, edge->v1, edge->weight);
    }
    else {
        v2->out_list->add(v2->out_list, edge->v1, edge->weight);
        v1->in_list->add(v1->in_list, edge->v2, edge->weight);
    }

    graph->edges = realloc(graph->edges, sizeof(Edge) * (graph->number_of_edges + 1));
    graph->edges[graph->number_of_edges] = edge;

    graph->number_of_edges++;

    return IT_IS_OK;
}

Vertex * graph_get_vertex(Graph * graph, char * info) {
    if (graph == NULL) {
        fprintf(stderr, "tried to get vertex from null graph.\n");
        return NULL;
    }

    for (size_t i = 0; i < graph->number_of_vertexes; ++i) {
        if (!strcmp(info, graph->vertexes[i]->info)) {
            return graph->vertexes[i];
        }
    }

    return NULL;
}