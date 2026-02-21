#include <stdio.h>
#include <stdlib.h>

struct Child {
    int value;
    struct Child* next2;
};

struct Parent {
    struct Child* nrow;
    struct Parent* next;
};

void allocate(struct Parent** head, int n) {
    int current_rows = 0;
    struct Parent* cursor = *head;

    while (cursor != NULL) {
        current_rows++;
        struct Child* cCursor = cursor->nrow;
        
        int current_cols = 0;
        struct Child* lastChild = NULL;
        while (cCursor != NULL) {
            current_cols++;
            lastChild = cCursor;
            cCursor = cCursor->next2;
        }
        for (int j = current_cols; j < n; j++) {
            struct Child* newCol = malloc(sizeof(*newCol));
            newCol->value = 0;
            newCol->next2 = NULL;
            if (lastChild == NULL) {
                cursor->nrow = newCol;
            } else {
                lastChild->next2 = newCol;
            }
            lastChild = newCol;
        }
        cursor = cursor->next;
    }
    for (int i = current_rows; i < n; i++) {
        struct Parent* newNode = malloc(sizeof(*newNode));
        newNode->next = NULL;
        
        struct Child* colHead = NULL;
        struct Child* lastCol = NULL;
        for (int j = 0; j < n; j++) {
            struct Child* newCol = malloc(sizeof(*newCol));
            newCol->value = 0;
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

void iterate(struct Parent** head) {
    struct Parent* cursor = *head;  
    struct Child* cursor2;
    while(cursor != NULL) {
        cursor2 = cursor->nrow;
        while(cursor2 != NULL) {
            printf("%4d",cursor2->value);
            cursor2=cursor2->next2;
        }
        printf("\n");
    cursor=cursor->next;
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
    iterate(&head);
    
    return 0;
}
