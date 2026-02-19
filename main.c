#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void print(int** arr, int row) {
    for(int i=0; i<row; i++) {
        for(int j=0; j<row; j++) {
            printf("%d",arr[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int row = 4;
    int** arr = malloc(row*sizeof(*arr));

    for(int i=0; i<row; i++) {
        arr[i] = malloc(row*sizeof(**arr));
        for(int j=0; j<row; j++) {
            arr[i][j] = 0;
        }
    }
    arr[2][3] = 5;
    print(arr, row);

    for(int i=0; i<row; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}