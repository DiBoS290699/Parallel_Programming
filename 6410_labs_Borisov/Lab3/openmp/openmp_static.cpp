#include <omp.h> 
#define CHUNK 100 
#define NMAX 960001 
#include "stdio.h"


int main(int argc, char* argv[]) {
	int n_threads = 1;
	if (argc != 0) {
		n_threads = atoi(argv[1]);
	}
	printf("\n n_threads = %i \n", n_threads);
	omp_set_num_threads(n_threads);
	double avgTime;
	int N = NMAX; 
	int chunk = CHUNK;
	int iter;
	for (iter=0; iter < 10; iter++) { 	

		int i; 
		double* a = (double*) malloc(N * sizeof(double));
		double* b = (double*) malloc(N * sizeof(double)); 
		double* sum = (double*) malloc(N * sizeof(double)); 

		double st_time, end_time; 

		if (a == NULL || b == NULL || sum == NULL) {
			printf("This array is so big!");
			return 1;
		} 

		for (i=0; i < N; i++) {
			a[i] = 0.5;
			b[i] = 0.5;
		}
	
		st_time = omp_get_wtime(); 
		
		#pragma omp parallel for shared (a, b, sum, N) private (i) schedule(static,chunk)
			for (i=0; i < N; i++){ 
				sum[i] = b[i] + a[i]; 
			} 
								
	
	 	end_time = omp_get_wtime (); 
		end_time = end_time - st_time; 
	
		avgTime = avgTime + end_time;
		free(a);
		free(b);
		//printf("\nSum: ");
		//for (int k = N - 1; k > N - 16; --k) {
		//	printf("%f ", sum[k]);
		//}
		//printf("\n");
		free(sum);
	}
	printf("OMP static Version with CHUNK = %d\n", chunk); 	
	printf("AVERAGE TIME OF WORK IS %f \n", avgTime / 10); 
	return 0; 
} 
