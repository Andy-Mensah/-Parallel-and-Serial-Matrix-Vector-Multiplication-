/*Functions for vector-vector multiplication using serial
and parallel programming together with timing function.
*/

#include <time.h>
#include "mpi.h"

/*
Function for vector-vector multiplication
argument: number of elements of two array, two array buffer for operational matrix
return answer as a double.
*/

double vector_vector (int m, int n, double *vecA, double *vecB){
    double results = 0;
    for (int i = 0; i < m; i++){
        results += (vecA[i]*vecB[i]); 
    }
    return results;
}


/*
function for vector vector multiplication in parallel
argument: number of elements, two array buffer for operational matrix
return answer as a double.
*/

double mpi_vector_vector(int rank, int local_n, double *vecA, double *vecB){
    
    // declare local variables
    int root = 0;
    double local_result = 0, global_result = 0;

    // vector multiplication for every rank 
    for (int i = 0; i < local_n; i++){
        local_result += (vecA[i]*vecB[i]);
    }
    // complile results in root 
    if (rank == root){
        global_result = local_result;
        MPI_Reduce(MPI_IN_PLACE, (void *)&global_result, 1, MPI_DOUBLE, MPI_SUM, root, MPI_COMM_WORLD);
    }
    else {
        MPI_Reduce((void *)&local_result, (void *)&global_result, 1, MPI_DOUBLE, MPI_SUM, root, MPI_COMM_WORLD);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == root)
    return global_result; 
}


/*
function for timing function in this source file
argument: funtion to time, arguments needed by function
*/
double runtime_vec_vec(double (*function) (int, int, double*, double*),
                    int m , int n, double *vecA, double *vecB)
{
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


