#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "4170120_vector.h"
#include "4170120_matrix.h"
#define CORE 1
#define N 900

int main(int argc, char * argv[]){
    int i;
    
    FILE * filehandler = NULL;
	filehandler = fopen("4170120_serial.txt" ,"w");
	if(filehandler == NULL){
		printf("File could not be opened!\n");
		exit(1);
	}
    fprintf(filehandler,"N\tCore\tV.V/s\tM.V/s\tM.M/s");
double mins;
    

for(i=1; i<=N; i*=2){
    printf("================SIZE================ %d\n",i);    
    fprintf(filehandler,"\n%d\t%d\t", i, CORE);

    double* vecA = malloc(i*i * sizeof(double));
    double* vecB = malloc(i*i * sizeof(double));
    double* matA = malloc(i*i * sizeof(double));
    double* matB = malloc(i*i * sizeof(double));
    double* matC = malloc(i*i * sizeof(double));

    if (vecA == NULL || vecB == NULL || matA == NULL || matB == NULL || matC == NULL) {
        printf("Memory allocation failed. Exiting...\n");
        // Handle memory allocation failure and exit the program
        if (vecA) free(vecA);
        if (vecB) free(vecB);
        if (matA) free(matA);
        if (matB) free(matB);
        if (matC) free(matC);
        fclose(filehandler);
        exit(1);
    }
    double vec_vec = runtime_vec_vec(vector_vector, i, i, vecA, vecB);
    // mins = vec_vec/60;
    printf("vecvec = %lfsecs\n",vec_vec);
    // printf("vecvec = %lfmins\n\n",mins);
    

    double mat_vec = runtime_mat_vec(matrix_vector, i, i, vecA, matA, matC);
    // mins = mat_vec/60;
    printf("matvec = %lfsecs\n",mat_vec);
    // printf("matvec = %lfmins\n\n",mins);
    

    double mat_mat = runtime_mat_mat(matrix_matrix, i, i, matA, matB, matC);
    // mins = mat_mat/60;
    printf("matmat = %lfsecs\n",mat_mat);
    // printf("matmat = %lfmins\n\n",mins);


    fprintf(filehandler,"%lf\t",vec_vec);
    fprintf(filehandler,"%lf\t",mat_vec);
    fprintf(filehandler,"%lf",mat_mat);
    // fprintf(filehandler,"\n");
    
    free(vecA);
    free(vecB);
    free(matA);
    free(matB);
    free(matC);
    // matA = matB = matC = vecA = vecB = NULL;
}

    printf("............Written to file...................\n\n\n");
    fclose(filehandler);
    return 0;
}
