//function protypes for vector.c source file
double vector_vector (int m, int n, double *vecA, double *vecB);

double mpi_vector_vector(int rank, int local_n, double *vecA, double *vecB);

double runtime_vec_vec(double (*function) (int, int, double*, double*),
                    int m , int n, double *vecA, double *vecB);
