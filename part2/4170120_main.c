#include <stdio.h>
#include <stdlib.h>
#include "4170120_vector.h"
#include "mpi.h"
#define ROOT 0


int main(int argc, char *argv []){
    if ((argc != 3)){
        printf("%s", "error: invalid arguments.\n");
        exit(1);
    }

    const int N  = atoi(argv[1]);
    const int CORE = atoi(argv[2]);

    // Declare variables
    int rank, size, local_N;
    double *vecA, *vecB, *localVecA, *localVecB, result;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    if (rank == ROOT){ 
    // Declare Vectors buffers
    vecA = (double*)malloc(N*sizeof(double));
    vecB = (double*)malloc(N*sizeof(double));
    
    
    // populate buffers with arbitary values
    for (int i = 0; i < N; i++){
        vecA[i] = i;
        vecB[i] = i+1;
    } 
    }

    // calculate vector size for each rank
    local_N = N/size;

    localVecA = (double *) malloc(local_N*sizeof(double));
    localVecB = (double *) malloc(local_N*sizeof(double));
    
    MPI_Scatter(vecA, local_N, MPI_DOUBLE, localVecA, local_N, MPI_DOUBLE, ROOT, MPI_COMM_WORLD);
    MPI_Scatter(vecB, local_N, MPI_DOUBLE, localVecB, local_N, MPI_DOUBLE, ROOT, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    double veclocaltime = runtime_vec_vec(mpi_vector_vector, rank, local_N, localVecA, localVecB);
    double vecMaxTime;
    MPI_Reduce((void *)&veclocaltime, (void *)&vecMaxTime, 1, MPI_DOUBLE, MPI_MAX, ROOT, MPI_COMM_WORLD);

    if (rank == ROOT){
    // Declare a file pointer
    FILE *fHandler;

    // Open a file with append mode;
    fHandler = fopen("4170120_scale.txt", "a+");

    // Check if opening file was succesful
    if (fHandler == NULL){
        printf("\nFile could not be opened");
        exit(1);
    }

    // Print heading to file
    char empty;
    if(fscanf(fHandler, "%c", &empty) == EOF)
        fprintf(fHandler, "%-9s\t%-4s\t%-8s\t%-8s\t%-8s\n", "N", "Core", "V.V/s", "M.V/s", "M.M/s");

    // Print to file
    fprintf(fHandler, "%-9d\t%-4d\t%-8lf\t%-8s\t%-8s\n", N, CORE, vecMaxTime, "---", "---");


    // Close file
    fclose(fHandler);

   
    free(vecA);
    free(vecB);
    }

    free(localVecA);
    free(localVecB);

    

    MPI_Finalize();
    return 0;
}



