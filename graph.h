#ifndef GRAPH_H
#define GRAPH_H

#define N 5   // jumlah node dalam graph
/* Index node:
   A = 0  (BO)
   D = 1  (Indomaret SA)
   G = 2  (Gacoan Tlogomas)
   E = 3  (Masjid AT)
   I = 4  (UM Veteran)
*/

// Deklarasi fungsi
void printGraph(int graph[N][N]);
void dijkstra(int graph[N][N], int start);

#endif