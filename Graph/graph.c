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

    graph->vertexes = malloc(sizeof(Vertex));
    graph->edges = malloc(sizeof(Vertex));
    graph->number_of_edges = 0;
    graph->number_of_vertexes = 0;
    graph->size_v = 1;
    graph->size_e = 1;

    graph->add_vertex = graph_add_vertex;
    graph->add_edge = graph_add_edge;
    graph->get_vertex = graph_get_vertex;
    graph->print = print_graph;
    graph->free = graph_free;
    graph->get_vertex_index = graph_get_vertex_index;
    graph->get_edge = graph_get_edge;
    graph->get_edge_index = graph_get_edge_index;
    graph->delete_edge = graph_delete_edge;
    graph->delete_vertex = graph_delete_vertex;
    graph->BFS = graph_BFS;

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

    if (graph->number_of_vertexes == graph->size_v) {
        graph->size_v *= 2;
        graph->vertexes = realloc(graph->vertexes, sizeof(Vertex) * (graph->size_v + 1));
    }
    vertex_copy(graph->vertexes + graph->number_of_vertexes, vertex);
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

    Vertex * v1 = graph->get_vertex(graph, edge->v1.info);
    Vertex * v2 = graph->get_vertex(graph, edge->v2.info);
    Edge * e = graph->get_edge(graph, edge);

    if (v1 == NULL || v2 == NULL) {
        fprintf(stderr, "there is not vertex such as in edge.\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }
    if (e) {
        edge->free(edge);
        return IT_IS_OK;
    }
//
//    // проверяем что действительно добавили
//    if (v1 == NULL || v2 == NULL) {
//        fprintf(stderr, "Error!!! v1 or v2 was not added.\n");
//        exit(RUNTIME_ERROR);
//    }

    if (edge->orientation == V1_to_V2) {
        v1->add_edge(v1, edge);
        v2->add_edge(v2, edge);
    }
    else {
        v1->add_edge(v2, edge);
        v2->add_edge(v1, edge);
//        v2->out_list->add(v2->out_list, edge->v1, edge->weight);
//        v1->in_list->add(v1->in_list, edge->v2, edge->weight);
    }

    if (graph->number_of_edges == graph->size_e) {
        graph->size_e *= 2;
        graph->edges = realloc(graph->edges, sizeof(Edge) * (graph->size_e + 1));
    }
    //graph->edges = realloc(graph->edges, sizeof(Edge*) * (graph->number_of_edges + 1));
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
        if (!strcmp(info, graph->vertexes[i].info)) {
            return graph->vertexes + i;
        }
    }

    return NULL;
}

size_t graph_get_vertex_index(Graph * graph, char * name) {
    if (graph == NULL) {
        fprintf(stderr, "tried to get vertex from null graph.\n");
        return 0;
    }

    for (size_t i = 0; i < graph->number_of_vertexes; ++i) {
        if (!strcmp(name, graph->vertexes[i].info)) {
            return i;
        }
    }

    return graph->number_of_vertexes;
}

size_t _index(Vertex * vs, Vertex * v) {
    if (v == NULL || vs == NULL) {
        fprintf(stderr, "null is here.\n");
        return -1;
    }

    return ((size_t) v - (size_t) vs) / sizeof(Vertex);
}

size_t graph_get_edge_index(Graph * graph, Edge * edge) {
    if (graph == NULL) {
        fprintf(stderr, "tried to get edge index from null graph.\n");
        return 0;
    }

    for (size_t i = 0; i < graph->number_of_edges; ++i) {
        Edge * e = graph->edges[i];
        if (!strcmp(edge->v1.info, e->v1.info) && !strcmp(edge->v2.info, e->v2.info) && edge->orientation == e->orientation) {
            return i;
        }
        if (!strcmp(edge->v2.info, e->v1.info) && !strcmp(edge->v1.info, e->v2.info) && e->orientation != edge->orientation) {
            return i;
        }
    }

    return graph->number_of_edges;
}

Edge * graph_get_edge(Graph * graph, Edge * edge) {
    if (graph == NULL) {
        fprintf(stderr, "tried to get edge from null graph.\n");
        return 0;
    }

    for (size_t i = 0; i < graph->number_of_edges; ++i) {
        Edge * e = graph->edges[i];
        bool if1 = !strcmp(edge->v1.info, e->v1.info) && !strcmp(edge->v2.info, e->v2.info) && edge->orientation == e->orientation;
        bool if2 = !strcmp(edge->v1.info, e->v2.info) && !strcmp(edge->v2.info, e->v1.info) && edge->orientation != e->orientation;
        if (if1 || if2) {
            return graph->edges[i];
        }
    }

    return NULL;
}

Error graph_free(Graph * graph) {
    if (graph == NULL) {
        fprintf(stderr, "null graph in freeing.\n");
        return FREEING_OF_NULL_PTR;
    }

    for (size_t i = 0; i < graph->number_of_vertexes; ++i)
        graph->vertexes[i].free(graph->vertexes[i]);
    for (size_t i = 0; i < graph->number_of_edges; ++i)
        graph->edges[i]->free(graph->edges[i]);

    free(graph->edges);
    free(graph->vertexes);

    free(graph);

    return IT_IS_OK;
}

Error graph_delete_edge(Graph * graph, Edge * edge) {
    if (graph == NULL) {
        fprintf(stderr, "иди ...\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }
    if (edge == NULL) {
        fprintf(stderr, "иди ...\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }

    Vertex * v1 = graph->get_vertex(graph, edge->v1.info);
    Vertex * v2 = graph->get_vertex(graph, edge->v2.info);
    Edge * e = graph->get_edge(graph, edge);

    if (v1 == NULL || v2 == NULL) {
        fprintf(stderr, "there is not such vertexes in this graph.\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }
    if (e == NULL) {
        return IT_IS_OK;
    }

    if (edge->orientation == V1_to_V2) {
        v1->out_list->delete(v1->out_list, edge->v2.info);
        v2->in_list->delete(v2->in_list, edge->v1.info);
    } else {
        v2->out_list->delete(v2->out_list, edge->v1.info);
        v1->in_list->delete(v1->in_list, edge->v2.info);
    }

    size_t ind = graph->get_edge_index(graph, edge);
    if (ind >= graph->number_of_edges) {
        fprintf(stderr, "there is not such edge.\n");
        edge->free(edge);
        return RUNTIME_ERROR;
    }

    graph->edges[ind]->free(graph->edges[ind]);
    memmove(graph->edges + ind, graph->edges + ind + 1, sizeof(Edge *) * (graph->number_of_edges-ind-1));
    graph->number_of_edges--;
    graph->edges = realloc(graph->edges, sizeof(Edge *) * (graph->number_of_edges));

    if (graph->number_of_edges == 0) {
        graph->edges = NULL;
    }

    return IT_IS_OK;
}

Error graph_delete_vertex(Graph * graph, char * name) {
    Vertex *vertex = graph->get_vertex(graph, name);
    if (vertex == NULL) {
        fprintf(stderr, "there is no such vertex in this graph.\n");
        return RUNTIME_ERROR;
    }

    AdjacencyList *in_list = vertex->in_list;
    AdjacencyList *out_list = vertex->out_list;

    // что это ???!!!
//    AdjacencyListEl *El = in_list->head;
//    for (size_t i = 0; i < in_list->number_of_el; ++i) {
//        El->vertex->out_list->delete(El->vertex->out_list, vertex->info);
//    }
//    El = out_list->head;
//    for (size_t i = 0; i < out_list->number_of_el; ++i) {
//        El->vertex->in_list->delete(El->vertex->in_list, vertex->info);
//    }

    size_t ind = graph->get_vertex_index(graph, vertex->info);
    if (ind == graph->number_of_vertexes) {
        fprintf(stderr, "can't find current vertex in graph now.\n");
        exit(RUNTIME_ERROR);
    }

    Edge ** edges = NULL;
    size_t number_of_deleting_edges = 0;
    for (size_t i = 0; i < graph->number_of_edges; ++i) {
        if (!strcmp(graph->edges[i]->v1.info, vertex->info) || !strcmp(graph->edges[i]->v2.info, vertex->info)) {
            edges = realloc(edges, sizeof(Edge*) * (number_of_deleting_edges+1));
            edges[number_of_deleting_edges] = graph->edges[i];
            number_of_deleting_edges++;
        }
    }

    for (size_t i = 0; i < number_of_deleting_edges; ++i) {
        graph->delete_edge(graph, edges[i]);
    }
    free(edges);

    graph->vertexes[ind].free(graph->vertexes[ind]);
    memmove(graph->vertexes + ind, graph->vertexes + ind + 1, sizeof(Vertex) * (graph->number_of_vertexes-ind-1));
    graph->number_of_vertexes--;
    graph->vertexes = realloc(graph->vertexes, sizeof(Vertex) * (graph->number_of_vertexes));
    if (graph->number_of_vertexes == 0) {
        graph->vertexes = NULL;
    }

    return IT_IS_OK;
}

Vertex ** graph_BFS(Graph * graph, Vertex * start_vertex, char * name) {
    if (graph == NULL) {
        fprintf(stderr, "null graph in BFS.\n");
        return NULL;
    }
    if (graph->vertexes == NULL) {
        return NULL;
    }
    if (start_vertex == NULL) {
        start_vertex = graph->vertexes;
        fprintf(stderr, "start vertex is null, so we started from 0 index vertex.\n");
    }


    size_t depth = 0;
    Vertex ** path = BFS(graph, start_vertex, name, &depth);
    if (path == NULL)
        return NULL;
    path = realloc(path, sizeof(Vertex*) * (depth+2));
    path[depth+1] = NULL;

    return path;
}