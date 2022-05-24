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

        double weight = atof(numbers[3]);

        Edge * edge = edge_init(*vv1, *vv2, V1_to_V2, weight);
        graph->add_edge(graph, edge);

        long number = atol(numbers[0]);
        if (number % 1000 == 0)
            printf("%ld\n", number);

        free(numbers[0]);
        free(numbers[3]);
        //free(numbers[4]);
        free(numbers);

        if (number > 1000) {
            break;
        }
    }

    fclose(file);

    return graph;
}