#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "4170120_vector.h"
// #define N (m*n)



double vector_vector( int m, int n, double * vecA , double * vecB ){
    int i;
    
    for(i = 0; i<n; i++){
        vecA[i] = 3;
        vecB[i] = 4;
    }

    //Multiplying the vectors
    double mult = 0.0;
    for(i=0; i<n; i++){
            mult += (vecA[i] * vecB[i]);
        }
    return mult;
}

double runtime_vec_vec(double (*function)(int, int, double*, double*), int m, int n, double* vecA, double* vecB) {
    // Starting timer
    struct timespec start;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    
    function(m, n, vecA, vecB);

    // Ending timer
    struct timespec end;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    // Calculating runtime
    double diff = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    return diff;
}

