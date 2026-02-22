#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Child {
    int value;
    int index2;
    struct Child* next2;
};

struct Parent {
    struct Child* nrow;
    int index;
    int currentShortest;
    bool isExplored;
    struct Parent* next;
};

void allocate(struct Parent** head, int n);
void modify(struct Parent** head, int val, int m, int n);
void updateEstimate(struct Parent** head, int updatedIndex, int updatedValue);
int dijkstra(struct Parent** head, int target);
void printGraph(struct Parent** head);

#endif
