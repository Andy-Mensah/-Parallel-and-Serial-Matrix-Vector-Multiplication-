void matrix_vector(int m, int n, double * matA, double * vecA, double * matC);
double runtime_mat_vec(void (*function)(int, int , double *, double *, double *), int m, int n, double * matA , double * vecA, double * matC );


void matrix_matrix(int m, int n, double * matA, double * matB, double * matC);
double runtime_mat_mat(void (*function)(int, int , double *, double *, double *), int m, int n, double * matA , double * matB, double * matC );
