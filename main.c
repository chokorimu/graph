#include "graph.h"

int main() {
    struct Parent* head = NULL;

    allocate(&head, 5);
    modify(&head, 6, 1, 2);
    modify(&head, 7, 1, 4);
    modify(&head, 12, 2, 3);
    modify(&head, 10, 3, 5);
    modify(&head, 21, 4, 3);
    modify(&head, 28, 4, 5);
    printGraph(&head);
    printf("%d\n", dijkstra(&head, 4));
    
    return 0;
}
