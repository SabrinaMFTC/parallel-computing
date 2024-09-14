#include <stdio.h>
#include <stdlib.h>
#define MAXN 1000

void printMatrix(long** m) {
    for (int i = 0; i < MAXN; ++i) {
        printf("|");
        for (int j = 0; j < MAXN; ++j) {
            printf(" %ld ", m[i][j]);
        }
        printf("|\n");
    }
    printf("\n");
}

long max(long** m) {
    return m[MAXN-1][MAXN-1];
}

int main() {
    // Dynamically allocating memory for the matrixes
    long** a = (long**)malloc(MAXN * sizeof(long*));
    long** b = (long**)malloc(MAXN * sizeof(long*));
    long** c = (long**)calloc(MAXN, sizeof(long*));

    for (int i = 0; i < MAXN; ++i) {
        a[i] = (long*)malloc(MAXN * sizeof(long));
        b[i] = (long*)malloc(MAXN * sizeof(long));
        c[i] = (long*)calloc(MAXN, sizeof(long)); 
    }

    // Filling the matrixes
    int value = 1;

    for (int i = 0; i < MAXN; ++i) {
        for (int j = 0; j < MAXN; ++j) {
            a[i][j] = b[i][j] = value++;
        }
    }

    // Multiplying the matrixes (1st algorithm = without cache optimization)
    // for (int i = 0; i < MAXN; ++i) {
    //     for (int j = 0; j < MAXN; ++j) {
    //         for (int k = 0; k < MAXN; ++k) {
    //             c[i][j] += a[i][k] * b[k][j];
    //         }
    //     }
    // }

    // Multiplying the matrixes (2nd algorithm = with cache optimization)
    for (int i = 0; i < MAXN; ++i) {
        for (int k = 0; k < MAXN; ++k) {
            for (int j = 0; j < MAXN; ++j) {
                c[i][j] = a[i][k] * b[k][j];
            }
        }
    }

    // Printing the matrixes
    // printMatrix(a);
    // printMatrix(b);
    // printMatrix(c);

    // Printing the max value to determine the best variable type
    // long maxValue = max(c);
    // printf("Max Value = %ld\n", maxValue);

    // Freeing the memory
    for (int i = 0; i < MAXN; ++i) {
        free(a[i]); free(b[i]); free(c[i]);
    }

    free(a); free(b); free(c);

    return 0;
}
