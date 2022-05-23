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
    Error (*delete)(AdjacencyList *, char * name);
    Error (*print)(AdjacencyList *);
};
AdjacencyList * adj_list_init(Vertex ** vertexes, size_t number_of_vertexes);
Error adj_list_free(AdjacencyList * list);
Error adj_list_add(AdjacencyList *, Vertex *, int weight);
Error adj_list_delete(AdjacencyList * list, char * name);
Error adj_list_print(AdjacencyList * list);

//==========================VERTEX=========================

struct Vertex {
    AdjacencyList * out_list;
    AdjacencyList * in_list;
    char * info;

    Error (* free)(Vertex*);
    Error (* add_edge)(Vertex*, Edge*);
    Error (* delete_edge)(Vertex*, Edge*);
    Error (* print)(Vertex *);
};
Vertex * vertex_init(char * info);
Error vertex_free(Vertex * vertex);
Vertex * vertex_enter();
Error vertex_add_edge(Vertex * vertex, Edge * edge);
Error vertex_delete_edge(Vertex * vertex, Edge * edge);
Error vertex_print(Vertex * v);
bool is_incidental(Vertex * v1, char * name);

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
    Vertex * vertexes;
    size_t number_of_vertexes;

    Edge ** edges;
    size_t number_of_edges;

    Error (*add_vertex)(Graph *, Vertex *);
    Error (*free)(Graph * graph);
    Error (*add_edge)(Graph *, Edge *);
    Vertex * (*get_vertex)(Graph *, char *);
    size_t (*get_vertex_index)(Graph *, char *);
    Edge * (*get_edge)(Graph *, Vertex *, Vertex *);
    size_t (*get_edge_index)(Graph *, Edge *);
    Error (*print)(Graph *, FILE *);
    Error (*delete_edge)(Graph *, Edge*);
    Error (*delete_vertex)(Graph *, char * name);
    Vertex ** (*BFS)(Graph *, Vertex *, char *);
};
Graph * graph_init(Vertex ** vertexes, Edge ** edges);
Error graph_free(Graph * graph);
Error graph_add_vertex(Graph * graph, Vertex * vertex);
Error graph_add_edge(Graph * graph, Edge * edge);
Vertex * graph_get_vertex(Graph * graph, char * info);
size_t graph_get_vertex_index(Graph * graph, char *);
Edge * graph_get_edge(Graph * graph, Vertex *, Vertex *);
size_t graph_get_edge_index(Graph * graph, Edge *);
Error print_graph(Graph * graph, FILE * stream);
Error graph_delete_edge(Graph * graph, Edge * edge);
Error graph_delete_vertex(Graph * graph, char * name);
size_t _index(Vertex * vs, Vertex * v);
Vertex ** BFS(Graph * graph, Vertex * start_v, char * name, size_t * depth);
Vertex ** graph_BFS(Graph * graph, Vertex * start_vertex, char * name);

#endif //LAB5_MYGRAPH_H
