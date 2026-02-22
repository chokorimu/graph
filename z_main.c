// main.c
#include <stdio.h>
#include "graph.h"

int main() {

    // Membuat graph dalam bentuk adjacency matrix
    int graph[N][N] = {
        //A   D   G   E   I
        { 0,  6,  0,  7,  0 },   // A = BO
        { 0,  0, 12,  0,  0 },   // D = Indomaret SA
        { 0,  0,  0,  0, 16 },   // G = Gacoan Tlogomas
        { 0,  0, 21,  0, 28 },   // E = Masjid AT
        { 0,  0,  0,  0,  0 }    // I = UM Veteran
    };

    printf("Adjacency Matrix:\n");
    printGraph(graph);

    printf("\nHasil Dijkstra dari node A (BO):\n");
    dijkstra(graph, 0);   // mulai dari A

    return 0;
}