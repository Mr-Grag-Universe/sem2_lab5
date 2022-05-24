//
// Created by Stephan on 24.05.2022.
//
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

#include "Errors.h"
#include "FGetLine.h"
#include "MyString.h"
#include "mygraph.h"


Vertex vertex_e(char * name) {
    char * line = NULL;
    do {
        if (line)
            free(line);
        line = name;
    } while (line == NULL || line[0] == '\0');

    Vertex vertex = vertex_init(line);

    return vertex;
}

Error add_vertex_l(Graph * graph, char * name) {
    Vertex v = vertex_e(name);

    Vertex * v1 = graph->get_vertex(graph, v.info);
    if (v1) {
        v.free(v);
        return IT_IS_OK;
    }

    Error report = graph->add_vertex(graph, &v);

    return report;
}

Edge * edge_e(char * name1, char * name2, double weight, bool enter_weight) {
    //printf("Enter your label1: ");
    //char * v1_label = NULL;
    //do {
    //    if (v1_label)
    //        free(v1_label);
    char * v1_label = name1;
    //} while (v1_label == NULL || v1_label[0] == '\0');

    // printf("Enter your label2: ");
    char * v2_label = name2;
//    do {
//        if (v2_label)
//            free(v2_label);
//        v2_label = name2;
//    } while (v2_label == NULL || v2_label[0] == '\0');

    Vertex v1 = vertex_init(v1_label);
    Vertex v2 = vertex_init(v2_label);

    Edge * edge = edge_init(v1, v2, V1_to_V2, 1);
    if (enter_weight) {
        edge->weight = weight;
    }

    return edge;
}

Error add_edge_l(Graph * graph, char * name1, char * name2, double weight) {
    Edge * edge = edge_e(name1, name2, weight, 0);

    Vertex * v1 = graph->get_vertex(graph, edge->v1.info);
    Vertex * v2 = graph->get_vertex(graph, edge->v2.info);

    if (v1 == NULL || v2 == NULL) {
        return WRONG_INPUT_FROM_STREAM;
    }
    edge->v1.free(edge->v1);
    edge->v2.free(edge->v2);
    vertex_copy(&edge->v1, v1);
    vertex_copy(&edge->v2, v2);
    // можно сделать добавление если нет вершины

    Error report = graph->add_edge(graph, edge);

    return report;
}

Graph * read_graph() {
    FILE * file = fopen("data.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "there is no such file in this directory.\n");
        return NULL;
    }

    Graph * graph = graph_init(NULL, NULL);

    while (feof(file) != EOF) {
        char * line = f_get_line(file, ftell(file));
        if (line == NULL || line[0] == '\0') {
            if (line)
                free(line);
            break;
        }

        char ** numbers = split(line, " \t\n");


        free(line);
        if (numbers == NULL) {
            printf("numbers is null");
            break;
        }

//        Vertex * v1 = graph->get_vertex(graph, numbers[1]);
//        bool f1 = 0;
//        if (v1 == NULL) {
//            f1 = 1;
//            v1 = malloc(sizeof(Vertex));
//            Vertex v_tmp = vertex_init(numbers[1]);
//            vertex_copy(v1, &v_tmp);
//            graph->add_vertex(graph, v1);
//            char * name = v1->info;
//            free(v1);
//            v1 = graph->get_vertex(graph, name);
//        } else {
//            free(numbers[1]);
//        }
//        bool f2 = 0;
//        Vertex * v2 = graph->get_vertex(graph, numbers[2]);
//        if (v2 == NULL) {
//            f2 = 1;
//            v2 = malloc(sizeof(Vertex));
//            Vertex v_tmp = vertex_init(numbers[2]);
//            vertex_copy(v2, &v_tmp);
//            graph->add_vertex(graph, v2);
//            char * name = v2->info;
//            free(v2);
//            v2 = graph->get_vertex(graph, name);
//        } else {
//            free(numbers[2]);
//        }
/*
        Vertex v1 = vertex_init(numbers[1]);
        Vertex v2 = vertex_init(numbers[2]);

        Vertex * vv1 = graph->get_vertex(graph, v1.info);
        Vertex * vv2 = graph->get_vertex(graph, v2.info);

        if (vv1 == NULL) {
            graph->add_vertex(graph, &v1);
            vv1 = graph->get_vertex(graph, v1.info);
        }
        else {
            v1.free(v1);
            vertex_copy(&v1, vv1);
        }
        if (vv2 == NULL) {
            graph->add_vertex(graph, &v2);
            vv2 = graph->get_vertex(graph, v2.info);
        }
        else {
            v2.free(v2);
            vertex_copy(&v2, vv2);
        }


        Edge * edge = edge_init(*vv1, *vv2, V1_to_V2, weight);
        graph->add_edge(graph, edge);
*/
        double weight = atof(numbers[3]);

        char * name1 = str_copy(numbers[1]);
        char * name2 = str_copy(numbers[2]);

        add_vertex_l(graph, numbers[1]);
        add_vertex_l(graph, numbers[2]);
        add_edge_l(graph, name1, name2, weight);

        long number = atol(numbers[0]);
        if (number % 1000 == 0)
            printf("%ld\n", number);

        free(numbers[0]);
        free(numbers[3]);
        free(numbers);

        if (number > 10000) {
            break;
        }
    }

    fclose(file);

    return graph;
}