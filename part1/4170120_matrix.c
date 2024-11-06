#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "4170120_matrix.h"



void matrix_vector(int m, int n, double * matA, double * vecA, double * matC){
    int i;
    
     for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matA[i * m + j] = 2;
        }
    }
for (i = 0; i < m; i++) {
        matC[i] = 0.0;
        for (int j = 0; j < n; j++) {
            matC[i] += vecA[j] * matA[i * n + j];
        }
    }
}

double runtime_mat_vec(void (*function)(int, int , double *, double *, double *), int m, int n, double * matA , double * vecA, double * matC ){
    // Starting timer
    struct timespec start;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    
    function(m, n, matA, vecA, matC);

    // Ending timer
    struct timespec end;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

    // Calculating CPU runtime
    double diff = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    return diff;
}


void matrix_matrix(int m, int n, double * matA, double * matB, double * matC){
    
    int i,j,k;

for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matB[i * m + j] = 1;
        }
    }


    for (i = 0; i < m; i++) {
        for (j = 0; j < m; j++) {
            matC[i * m + j] = 0.0;
            for (k = 0; k < n; k++) {
                matC[i * m + j] += matA[i * n + k] * matB[k * m + j];
            }
        }
    }
}

double runtime_mat_mat(void (*function)(int, int , double *, double *, double *), int m, int n, double * matA , double * matB, double * matC ){
    // Starting timer
    struct timespec start;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    
    function(m, n, matA, matB, matC);

    // Ending timer
    struct timespec end;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

    // Calculating CPU runtime
    double diff = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    return diff;
}





