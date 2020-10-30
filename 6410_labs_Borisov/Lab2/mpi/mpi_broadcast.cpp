#include <math.h> 
//#include <stdio.h> 
#include <stdlib.h> 
#include "mpi.h" 


int main(int argc, char* argv[]) { 

	double TotalSum, ProcSum = 0.0; 
	int ProcRank, ProcNum, N = 960000, i; 
	MPI_Status Status; 
	double* x = (double*) malloc(N * sizeof(double));
	double st_time, end_time; 

	MPI_Init(&argc,&argv); 

	MPI_Comm_size(MPI_COMM_WORLD,&ProcNum); 
	MPI_Comm_rank(MPI_COMM_WORLD,&ProcRank); 
	//printf("%i \n", ProcNum);

	if (ProcRank==0) { 
		for (i = 0; i < N; i++) x[i] = 1.0;	
	} 
	st_time = MPI_Wtime(); 

	MPI_Bcast(x, N, MPI_DOUBLE, 0, MPI_COMM_WORLD); 
	
	int k = N / ProcNum; 
	int i1 = k * ProcRank; 
	int i2 = k * ( ProcRank + 1 ); 

	if ( ProcRank == ProcNum-1 ) 
		i2 = N;

	for ( i = i1; i < i2; i++ ) {
		ProcSum = ProcSum + x[i]; 
	}

	MPI_Reduce(&ProcSum, &TotalSum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	MPI_Barrier(MPI_COMM_WORLD); 


	if ( ProcRank == 0 ) {
		printf("Broadcast version"); 
		printf("\nTotal Sum = %10.2f",TotalSum); 
		end_time = MPI_Wtime(); 
		end_time = end_time - st_time; 

		printf("\nTIME OF WORK IS %f \n\n", end_time); 
	} 

	MPI_Finalize(); 
	return 0; 
} 
