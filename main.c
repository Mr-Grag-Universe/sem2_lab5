#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdbool.h"
#include "KGetLine.h"
#include "time.h"
#include "MyString.h"
#include "commands.h"
#include "Errors.h"
#include "mygraph.h"
#include "dialog.h"

void clrscr(){
    system("@cls||clear");
}

char ** init_menu_points() {
    char ** menu_points = malloc(sizeof(char*) * (UNKNOWN_COMMAND));
    menu_points[EXIT] = "exit";
    menu_points[ADD_VERTEX] = "add a new vertex";
    menu_points[ADD_EDGE] = "add a new edge";
    menu_points[DELETE_VERTEX] = "delete an vertex";
    menu_points[DELETE_EDGE] = "delete an edge";
    menu_points[FIND_VERTEX] = "find an vertex";
    menu_points[DELETE_ALl] = "delete all";
    menu_points[TRAVERSAL] = "graph traversal";
    menu_points[TIMING] = "check out time";// of traversal and searching in BT";
    menu_points[RANDOM_GENERATE] = "generate random graph data";
    menu_points[READ_GRAPH] = "read graph from file";
    menu_points[GRAPHVIZ] = "update graphviz png";
    return menu_points;
}

void print_menu(char ** menu) {
    printf("This is menu:\n");
    for (int i = 0; i < UNKNOWN_COMMAND; ++i) {
        printf("%d) %s\n", i, menu[i]);
    }
}

bool check_command(char * command) {

    return true;
}

bool execute_command(Graph ** graph, Command command) {
    switch (command) {
        case EXIT: {
            printf("OK. Goodbye!\n");
            return true;
        }
        case ADD_VERTEX: {
            add_vertex_dialog(*graph);
            return false;
        }
        case ADD_EDGE: {
            add_edge_dialog(*graph);
            return false;
        }
        case FIND_VERTEX: {
            return false;
        }
        case DELETE_VERTEX: {
            return false;
        }
        case DELETE_EDGE: {
            return false;
        }
        case DELETE_ALl: {
            return false;
        }
        case TRAVERSAL: {
            char * answer = get_line();
            free(answer);
            return false;
        }
        case TIMING: {
            return false;
        }
        case RANDOM_GENERATE: {
            return false;
        }
        case READ_GRAPH: {
            return false;
        }
        case GRAPHVIZ: {
            dialog_update_graphviz(*graph);
            return false;
        }
        default: {
            printf("Your command is wrong!\n");
            return false;
        }
    }
    return false;
}

Command get_command_code(char * command) {
    if (is_digit(command)) {
        long int x = strtol(command, NULL, 10);
        if (x < 0 || x > UNKNOWN_COMMAND)
            return UNKNOWN_COMMAND;
        return x;
    }

    if (!strcmp(command, "exit"))
        return EXIT;
    else if (!strcmp(command, "get"))
        return FIND_VERTEX;
    else if (!strcmp(command, "add"))
        return ADD_VERTEX;
    else if (!strcmp(command, "delete"))
        return DELETE_VERTEX;
    else if (!strcmp(command, "delete all"))
        return DELETE_ALl;
    else if (!strcmp(command, "traversal"))
        return TRAVERSAL;
    else if (!strcmp(command, "time"))
        return TIMING;
    else if (!strcmp(command, "read"))
        return READ_GRAPH;
    else if (!strcmp(command, "graphviz"))
        return GRAPHVIZ;
    else return UNKNOWN_COMMAND;
}

Graph * start_session() {
    Graph * graph = graph_init(NULL, NULL);
    return graph;
}

int main() {
    printf("Edge: %ld, Vertex: %ld\n", sizeof(Edge), sizeof(Vertex));
    printf("Graph: %ld\n", sizeof(Graph));
    srand(time(NULL));
    bool finish = false;
    char ** menu = init_menu_points();

    printf("%ld", sizeof(NULL));

    Graph * graph = start_session();
    if (graph == NULL) {
        fprintf(stderr, "graph is NULL.\nSomething came wrong.\nCheck creation or initial data\n");
        exit(NULL_PTR_IN_UNEXCITED_PLACE);
    }

    while (!finish) {
        /// clrscr();
        print_menu(menu);

        char * command = get_line();
        if (command[0] == '\0') {
            free(command);
            continue;
        }
        //delete_double_spaces(&command);

        if (check_command(command) == false) {
            printf("Your command is wrong.");
            free(command);
            continue;
        }

        Command command_code = get_command_code(command);

        finish = execute_command(&graph, command_code);

        free(command);
    }
    graph->free(graph);
    free(menu);

    return 0;
}