//
// Created by Stephan on 23.05.2022.
//

#ifndef LAB5_BFS_DFS_H
#define LAB5_BFS_DFS_H
#include "mygraph.h"

typedef enum Q_mode {
    HEAD,
    TAIL,
} Q_mode;

typedef enum Color {
    BLACK,
    GREY,
    WHITE,
} Color;

typedef struct El {
   Vertex * v;
   struct El * next;
   struct El * pr;
   Color color;
   size_t depth;
} El;

typedef struct Queue {
    size_t number_of_elements;
    El * head;
    El * tail;
} Queue;

#endif //LAB5_BFS_DFS_H
