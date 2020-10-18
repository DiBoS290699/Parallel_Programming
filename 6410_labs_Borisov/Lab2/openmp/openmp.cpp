#include <omp.h> 
#define CHUNK 100 
#include "stdio.h" 


int main(int argc, char* argv[]) { 
	omp_set_num_threads(1);
	double avgTime;
	int iter;
	int N = 960000; 
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
	
	 	end_time = omp_get_wtime (); 
		end_time = end_time - st_time; 
	
		//printf("\nTotal Sum = %10.2f",sum); 
		avgTime = avgTime + end_time;
		free(a);
	}
	printf("AVERAGE TIME OF WORK IS %f \n", avgTime / 10); 
	return 0; 
} 
