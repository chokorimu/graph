#include <stdio.h>
#include <stdlib.h>

struct node2 {
    int value;
    struct node2* next2;
};

struct node {
    struct node2* nrow;
    struct node* next;
};

void allocate(struct node** Parent, int row) {
    for(int i=0; i<row; i++) {
        struct node2* newRow = malloc(sizeof(*newRow));
        newRow->value = 0;
        newRow->next2 = NULL;

        struct node* newNode = malloc(sizeof(*newNode));
        newNode->nrow = newRow;
        newNode->next = NULL;

        if(*Parent == NULL) {
            *Parent = newNode;
            continue;
        }
        struct node* cursor = *Parent;
        struct node2* cursor2 = cursor->nrow;
        while(cursor->next != NULL) {
            while(cursor2->next2) {
                cursor2 = cursor2->next2;
            }
            cursor2->next2 = newRow;
            cursor = cursor->next;
            cursor2 = cursor->nrow;
        }
        cursor->next = newNode;
    }
}

void iterate(struct node** Parent) {
    struct node* cursor = *Parent;  
    while(cursor != NULL) {
        struct node2* cursor2 = cursor->nrow;
        while(cursor2 != NULL) {
            printf("%d",cursor2->value);
            cursor2=cursor2->next2;
        }
        printf("\n");
        cursor2 = (*Parent)->nrow;
    cursor=cursor->next;
    }
}

int main() {
    struct node* Parent = NULL;
    struct node2* Child = NULL;
    allocate(&Parent, 4);
    iterate(&Parent);
    
    return 0;
}
