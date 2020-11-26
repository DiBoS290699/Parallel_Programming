#include <cstdlib>
#include <curand.h>
#include <cublas_v2.h>
#include <iostream>

#define IDX2F(i,j,ld) ((((j)-1)*(ld))+((i)-1))
#define IDX2C(i,j,ld) (((j)*(ld))+(i))


void GPU_fill_rand(float *A, int nr_rows_A, int nr_cols_A) {
    // Create a pseudo-random number generator 
    curandGenerator_t prng; 
    curandCreateGenerator(&prng, CURAND_RNG_PSEUDO_DEFAULT); 
    // Set the seed for the random number generator using the system clock 
    curandSetPseudoRandomGeneratorSeed(prng, (unsigned long long) clock()); 

    // Fill the array with random numbers on the device 
    curandGenerateUniform(prng, A, nr_rows_A * nr_cols_A); 
}

void single_thread_mmul(const float *A, const float *B, float *C, const int N) {
    int i, j, k;
    for(i=0; i < N; i++){
	for(j=0; j < N; j++){
 	    C[IDX2C(i, j, N)] = 0;
	    for(k=0; k < N; k++)
 		C[IDX2C(i, j, N)] += A[IDX2C(i, k, N)]*B[IDX2C(k, j, N)];
	}
    }
}


void gpu_blas_mmul(const float *A, const float *B, float *C, const int m, const int k, const int n) {
    int lda = m;
    int ldb = k;
    int ldc = m;
    const float alf = 1;
    const float bet = 0;
    const float *alpha = &alf;
    const float *beta = &bet;

    cublasHandle_t handle; 
    cublasCreate(&handle); 
    cublasSgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc); 
    cublasDestroy(handle); 
}


void print_matrix(const float *matrix, const int rows, const int cols) {
    std::cout << "[\n";
    for (int i = 0; i < rows; ++i) {
        std::cout << "[";
        for (int j = 0; j < cols; ++j) {
            std::cout << matrix[IDX2C(i, j, cols)] << ",\t";
        }
        std::cout << "],\n";
    }
    std::cout << "]\n";
}

int main(int argc, char* argv[]) { 
    int n = atoi(argv[1]); 
    std::cout << "NxN == " << n << "x" << n << "\n";
    int nr_rows_A, nr_cols_A, nr_rows_B, nr_cols_B, nr_rows_C, nr_cols_C; 
    nr_rows_A = nr_cols_A = nr_rows_B = nr_cols_B = nr_rows_C = nr_cols_C = n; 
    size_t malloc_size = nr_rows_A * nr_cols_A * sizeof(float);

    float *h_A = (float *)malloc(malloc_size); 
    float *h_B = (float *)malloc(malloc_size); 
    float *h_C = (float *)malloc(malloc_size); 

    float *d_A, *d_B, *d_C; 
    cudaMalloc(&d_A, malloc_size); 
    cudaMalloc(&d_B, malloc_size); 
    cudaMalloc(&d_C, malloc_size); 

    if (n == 3) {
        for (int j = 0; j < 9; j += 3) {
	    h_A[j] = 1;
	    h_A[j+1] = 2;
	    h_A[j+2] = 3;
        }

        for (int j = 0; j < 9; j += 3) {
	    h_B[j] = 9;
	    h_B[j+1] = 8;
	    h_B[j+2] = 7;
        }

        cudaMemcpy(d_A, h_A, malloc_size, cudaMemcpyHostToDevice); 
        cudaMemcpy(d_B, h_B, malloc_size, cudaMemcpyHostToDevice); 
    }
    else {
   	GPU_fill_rand(d_A, nr_rows_A, nr_cols_A); 
   	GPU_fill_rand(d_B, nr_rows_B, nr_cols_B);
        cudaMemcpy(h_A, d_A, malloc_size, cudaMemcpyDeviceToHost); 
        cudaMemcpy(h_B, d_B, malloc_size, cudaMemcpyDeviceToHost); 
    }

    if (n <= 3) {
        std::cout << "A =" << std::endl; 
        print_matrix(h_A, nr_rows_A, nr_cols_A); 
        std::cout << "B =" << std::endl; 
        print_matrix(h_B, nr_rows_B, nr_cols_B);
    }

    cudaEvent_t start, stop; 
    float gpuTime = 0.0f;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start, 0);

    gpu_blas_mmul(d_A, d_B, d_C, nr_rows_A, nr_cols_A, nr_cols_B); 

    //cudaDeviceSynchronize();
    cudaEventRecord(stop, 0);
    
    cudaMemcpy(h_C, d_C, malloc_size, cudaMemcpyDeviceToHost); 

    if (n <= 3) {
        std::cout << "C =" << std::endl; 
        print_matrix(h_C, nr_rows_C, nr_cols_C); 
    }

    cudaEventElapsedTime(&gpuTime, start, stop); 
    std::cout << "Time spent executing: " << gpuTime/1000 <<" seconds." << std::endl; 
 
    cudaFree(d_A); 
    cudaFree(d_B); 
    cudaFree(d_C);   
 
    free(h_A); 
    free(h_B); 
    free(h_C); 
    return 0;
}
