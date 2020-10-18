#include "mpi.h"
#include "stdio.h"
#include <time.h>
#include <math.h>
#include <omp.h>

int main(int argc, char* argv[])
{
clock_t start = clock();
int rank, ranksize, i;
MPI_Init(&argc, &argv);//
//Определяем свой номер в группе:
MPI_Comm_rank(MPI_COMM_WORLD, &rank); //
//Определяем размер группы:
MPI_Comm_size(MPI_COMM_WORLD, &ranksize);//
printf("Hello world from process %d from total number of %d\n", rank, ranksize);
clock_t end = clock();
double seconds = (double)(end - start) / CLOCKS_PER_SEC;
printf("The time: %f seconds\n", seconds);
MPI_Finalize();//
return 0;
}