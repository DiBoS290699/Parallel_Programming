#include <stdlib.h> 
#include "mpi.h"
#include <stdio.h>
#define NMAX 960001  


int main(int argc, char* argv[]) { 
	int ProcRank, ProcNum, N = NMAX, i, iter;
	MPI_Status Status; 
	double* a, *b, *sum, *loc_a, *loc_b, *loc_sum;
	int *send_counts, *displs, chunk = 100;
	double st_time, end_time, sum_time; 

	MPI_Init(&argc,&argv); 

	MPI_Comm_size(MPI_COMM_WORLD,&ProcNum); 
	MPI_Comm_rank(MPI_COMM_WORLD,&ProcRank); 

	for (iter = 0; iter < 10; ++iter) {
		int shift = N % ProcNum;
		int count = (N - shift) / ProcNum; 

		send_counts = (int*) malloc(ProcNum * sizeof(int)); 
		displs = (int*) malloc(ProcNum * sizeof(int));

		for (i = 0; i < ProcNum - 1; ++i) {
			send_counts[i] = count;
			displs[i] = count * i;
		}
		send_counts[ProcNum - 1] = count + shift;
		displs[ProcNum - 1] = count * (ProcNum - 1);

		if (ProcRank==0) {
			a = (double*) malloc(N * sizeof(double));
			b = (double*) malloc(N * sizeof(double));
			sum = (double*) malloc(N * sizeof(double));
			if (a == NULL || b == NULL || sum == NULL) {
				printf("This array is so big!");
				return 1;
			}

			for (i = 0; i < N; ++i) {
				a[i] = 0.5;
				b[i] = 0.5;
			}
		}

		loc_a = (double*) malloc(send_counts[ProcRank] * sizeof(double)); 
		loc_b = (double*) malloc(send_counts[ProcRank] * sizeof(double)); 
		loc_sum = (double*) malloc(send_counts[ProcRank] * sizeof(double)); 

		st_time = MPI_Wtime(); 

		MPI_Scatterv(a, send_counts, displs, MPI_DOUBLE, loc_a, send_counts[ProcRank], MPI_DOUBLE, 0, MPI_COMM_WORLD);
		MPI_Scatterv(b, send_counts, displs, MPI_DOUBLE, loc_b, send_counts[ProcRank], MPI_DOUBLE, 0, MPI_COMM_WORLD);

		for (i = 0; i < send_counts[ProcRank]; ++i) {
			loc_sum[i] = loc_a[i] + loc_b[i];
		}

		MPI_Gatherv(loc_sum, send_counts[ProcRank], MPI_DOUBLE, sum, send_counts, displs, MPI_DOUBLE, 0, MPI_COMM_WORLD);

		end_time = MPI_Wtime(); 
		end_time = end_time - st_time; 
		sum_time = sum_time + end_time;

		free(loc_a);
		free(loc_b);
		free(loc_sum);
	}

	if ( ProcRank == 0 ) {
		free(a);
		free(b);
		free(sum);
		free(send_counts);
		free(displs); 
		printf("MPI Version with NMAX = %d and CHUNK = %d\n", N, chunk);
		printf("AVERAGE TIME OF WORK IS %f \n", sum_time / 10); 
	} 
	MPI_Finalize(); 
	return 0;
} 
