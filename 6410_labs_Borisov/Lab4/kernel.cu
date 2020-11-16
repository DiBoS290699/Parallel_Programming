__global__ void addKernel(int *c, int *a, int *b, unsigned int size)
{
	// Тут располагается код функции ядра

	// Расчитываем индекс
	int index = blockIdx.x * blockDim.x + threadIdx.x;
	
	// Заполнение массива c
	c[index] = a[index] + b[index];
}

#define kernel addKernel
#include "Main.h"