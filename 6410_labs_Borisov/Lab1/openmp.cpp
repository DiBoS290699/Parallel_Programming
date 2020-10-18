#include <math.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <stdio.h>


int main(int argc, char* argv[])
{
	double start = omp_get_wtime();
	omp_set_num_threads(24);
	int nTheads, theadNum;
	#pragma omp parallel  private(nTheads, theadNum)
	{
		nTheads = omp_get_num_threads(); 
		theadNum = omp_get_thread_num(); 
		printf("OpenMP thread ?%d from %d threads \n", theadNum, nTheads);
	}
	printf("Time: %f", omp_get_wtime() - start);
	return 0;
}
