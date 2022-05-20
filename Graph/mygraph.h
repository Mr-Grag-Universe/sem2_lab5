//
// Created by Stephan on 18.05.2022.
//

#ifndef LAB5_MYGRAPH_H
#define LAB5_MYGRAPH_H
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"

#include "Errors.h"

typedef struct AdjacencyListEl AdjacencyListEl;
typedef struct AdjacencyList AdjacencyList;
typedef struct Edge Edge;
typedef struct Vertex Vertex;
typedef struct Graph Graph;

//=======================LIST ELEMENT=====================

struct AdjacencyListEl {
    Vertex *vertex;
    struct AdjacencyListEl *next;
    int weight;

    Error (*free)(AdjacencyListEl *);
};
AdjacencyListEl * adj_el_init(Vertex * vertex, AdjacencyListEl * next, int weight);
Error adj_el_free(AdjacencyListEl * el);

//=========================LIST======================

struct AdjacencyList {
    size_t number_of_el;
    AdjacencyListEl * head;
    AdjacencyListEl * tail;

    Error (*free)(AdjacencyList *);
    Error (*add)(AdjacencyList *, Vertex *, int weight);
};
AdjacencyList * adj_list_init(Vertex ** vertexes, size_t number_of_vertexes);
Error adj_list_free(AdjacencyList * list);
Error adj_list_add(AdjacencyList *, Vertex *, int weight);

//==========================VERTEX=========================

struct Vertex {
    AdjacencyList * out_list;
    AdjacencyList * in_list;
    char * info;

    Error (* free)(Vertex*);
    Error (* add_edge)(Vertex*, Edge*);
};
Vertex * vertex_init(char * info);
Error vertex_free(Vertex * vertex);
Vertex * vertex_enter();
Error vertex_add_edge(Vertex * vertex, Edge * edge);

//============================ORIENTATION==========================

typedef enum Orientation {
    V1_to_V2,
    V2_to_V1,
} Orientation;

//============================EDGE=============================

struct Edge {
    Vertex * v1;
    Vertex * v2;
    int weight;
    Orientation orientation;

    Error (*free)(Edge *);
};
Edge * edge_init(Vertex * v1, Vertex * v2, Orientation orientation, int weight);
Error edge_free(Edge * edge);
Edge * edge_enter(bool enter_weight);

//============================GRAPH===========================

struct Graph {
    Vertex ** vertexes;
    size_t number_of_vertexes;

    Edge ** edges;
    size_t number_of_edges;

    Error (*add_vertex)(Graph *, Vertex *);
    Error (*free)(Graph * graph);
    Error (*add_edge)(Graph *, Edge *);
    Vertex * (*get_vertex)(Graph *, char *);
    Error (*print)(Graph *, FILE *);
};
Graph * graph_init(Vertex ** vertexes, Edge ** edges);
Error graph_free(Graph * graph);
Error graph_add_vertex(Graph * graph, Vertex * vertex);
Error graph_add_edge(Graph * graph, Edge * edge);
Vertex * graph_get_vertex(Graph * graph, char * info);
Error print_graph(Graph * graph, FILE * stream);

#endif //LAB5_MYGRAPH_H
