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

void allocate(struct Parent** head, int n) {
    struct Parent* cursor = *head;
    int current_rows = 0;

    // Phase 1: Update existing rows and add missing columns
    while (cursor != NULL) {
        cursor->index = current_rows; 
        cursor->currentShortest = 2147483647; // Default "Infinity"
        cursor->isExplored = false;
        
        struct Child* cCursor = cursor->nrow;
        int current_cols = 0;
        struct Child* lastChild = NULL;
        
        // Traverse existing columns
        while (cCursor != NULL) {
            cCursor->index2 = current_cols; // Ensure existing child knows its column index
            lastChild = cCursor;
            cCursor = cCursor->next2;
            current_cols++;
        }
        
        // Add new columns to existing row if needed
        for (int j = current_cols; j < n; j++) {
            struct Child* newCol = malloc(sizeof(*newCol));
            newCol->value = 0;
            newCol->index2 = j; // Assign column index
            newCol->next2 = NULL;
            if (lastChild == NULL) cursor->nrow = newCol;
            else lastChild->next2 = newCol;
            lastChild = newCol;
        }
        current_rows++;
        cursor = cursor->next;
    }

    // Phase 2: Add brand new rows (nodes)
    for (int i = current_rows; i < n; i++) {
        struct Parent* newNode = malloc(sizeof(*newNode));
        newNode->index = i;
        newNode->currentShortest = 2147483647;
        newNode->isExplored = false;
        newNode->next = NULL;
        
        struct Child* colHead = NULL;
        struct Child* lastCol = NULL;
        for (int j = 0; j < n; j++) {
            struct Child* newCol = malloc(sizeof(*newCol));
            newCol->value = 0;
            newCol->index2 = j; // Assign column index
            newCol->next2 = NULL;
            if (colHead == NULL) colHead = newCol;
            if (lastCol != NULL) lastCol->next2 = newCol;
            lastCol = newCol;
        }
        newNode->nrow = colHead;

        if (*head == NULL) {
            *head = newNode;
        } else {
            struct Parent* rowSeeker = *head;
            while (rowSeeker->next != NULL) rowSeeker = rowSeeker->next;
            rowSeeker->next = newNode;
        }
    }
}

void modify(struct Parent** head, int val, int m, int n) {
    struct Parent* cursor = *head;
    for(int i=0; i<m-1; i++) {
        cursor=cursor->next;    
    }
    struct Child* cursor2 = cursor->nrow;
    for(int j=0; j<n-1; j++) {
        cursor2=cursor2->next2;    
    }
    cursor2->value = val;
}

void updateEstimate(struct Parent** head, int updatedIndex, int updatedValue) {
    struct Parent* cursor = *head;
    while(cursor != NULL && cursor->index != updatedIndex) {
        cursor = cursor->next;
    }
    if(cursor != NULL && updatedValue < cursor->currentShortest) {
        cursor->currentShortest = updatedValue;
    }
}

int dijkstra(struct Parent** head, int target) {
    if (*head != NULL) (*head)->currentShortest = 0;
    struct Parent* cursor = *head;

    while(cursor != NULL && cursor->index != target) {
        cursor->isExplored = true; 
        struct Child* cursor2 = cursor->nrow;

        while(cursor2 != NULL) {
            if(cursor2->value > 0) {
                int totalPath = cursor->currentShortest + cursor2->value;
                updateEstimate(head, cursor2->index2, totalPath);
            }
            cursor2 = cursor2->next2;
        }
        struct Parent* seeker = *head;
        struct Parent* bestNext = NULL;
        int minDistance = -1;

        while(seeker != NULL) {
            if(!seeker->isExplored && (seeker->currentShortest < minDistance || minDistance == -1)) {
                minDistance = seeker->currentShortest;
                bestNext = seeker;
            }
            seeker = seeker->next;
        }
        cursor = bestNext;
        if(cursor == NULL) break;
    }
    if (cursor != NULL && cursor->index == target) {
        return cursor->currentShortest;
    }
    return -1; 
}

void printGraph(struct Parent** head) {
    struct Parent* cursor = *head;  
    struct Child* cursor2;
    while(cursor != NULL) {
        cursor2 = cursor->nrow;
        while(cursor2 != NULL) {
            printf("%4d",cursor2->value);
            cursor2=cursor2->next2;
        }
        printf("\n");
    cursor = cursor->next;
    }
}

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
