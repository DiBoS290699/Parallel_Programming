#include <omp.h> 
#define CHUNK 100 
#include "stdio.h" 


int main(int argc, char* argv[]) {
	int n_threads = 1;
	if (argc != 0) {
		n_threads = atoi(argv[1]);
	}
	printf("\n n_threads = %i \n", n_threads);
	omp_set_num_threads(n_threads);
	double avgTime;
	int N = 960000; 
	int iter;
	for (iter=0; iter < 10; iter++) { 	

		int i; 
		double* a = (double*) malloc(N * sizeof(double));
		double sum;
		double st_time, end_time; 

		if (a == NULL) {
			printf("This array is so big!");
			return 1;
		} 

		for (i=0; i < N; i++) {
			a[i] = 1;
		}
	
		st_time = omp_get_wtime(); 
		sum = 0; 
		
		// #pragma omp parallel default(none) private(i) shared(nSum, nThreads, nStart, nEnd)
		#pragma omp parallel for reduction (+:sum)
			for (i=0; i < N; i++){ 
				sum = sum + a[i]; 
			} 
			//printf("\nTotal Sum = %10.2f",sum); 						
	
	 	end_time = omp_get_wtime (); 
		end_time = end_time - st_time; 
	
		avgTime = avgTime + end_time;
		free(a);
	}
	printf("OMP Reduction Version\n");

	printf("AVERAGE TIME OF WORK IS %f \n", avgTime / 10); 
	return 0; 
} 
