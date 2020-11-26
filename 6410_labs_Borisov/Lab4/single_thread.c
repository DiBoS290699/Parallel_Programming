#include <omp.h> 
#include "stdio.h"


int main(int argc, char* argv[]) {
	int n_threads = 1;
	int N = 0; 
	if (argc != 0) {
		N = atoi(argv[1]);
	}
	printf("\n n_threads = %i \n", n_threads);
	printf("\n N = %i \n", N);
	omp_set_num_threads(n_threads);
	double avgTime;
	int chunk = 100;
	int iter, *a, *b, *sum;
	for (iter=0; iter < 12; iter++) { 	

		int i; 
		a = (int*) malloc(N * sizeof(int));
		b = (int*) malloc(N * sizeof(int)); 
		sum = (int*) malloc(N * sizeof(int)); 

		double st_time, end_time; 

		if (a == NULL || b == NULL || sum == NULL) {
			printf("This array is so big!");
			return 1;
		} 

		for (i=0; i < N; i++) {
			a[i] = 1;
			b[i] = 2;
		}
	
		st_time = omp_get_wtime(); 
		
		#pragma omp parallel for shared (a, b, sum, N) private (i) schedule(dynamic,chunk)
			for (i=0; i < N; i++){ 
				sum[i] = b[i] + a[i]; 
			} 
								
	
	 	end_time = omp_get_wtime (); 
		end_time = end_time - st_time; 
	
		avgTime = avgTime + end_time;
		free(a);
		free(b);
	}
	printf("\nSum: ");
	int k;
	for (k = N - 1; k > N - 16; --k) {
		printf("%i ", sum[k]);
	}
	printf("\n");
	free(sum);

	printf("AVERAGE TIME OF WORK IS %f \n", avgTime / 12); 
	return 0; 
} 
