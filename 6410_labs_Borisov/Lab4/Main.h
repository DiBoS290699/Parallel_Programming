#include <cublas_v2.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{

    int n = atoi(argv[1]);

    printf("n = %d\n", n);

    int n2b = n * sizeof(int);

    // ��������� ������ �� �����
    int* a = (int*)calloc(n, sizeof(int));
    int* b = (int*)calloc(n, sizeof(int));
    int* c = (int*)calloc(n, sizeof(int));

    for (int i = 0; i < n; ++i) {
        a[i] = 1;
        b[i] = 2;
    }

    // ��������� ������ �� ����������
    int* dev_a = NULL;
    cudaError_t cuerr = cudaMalloc((void**)&dev_a, n2b);
    if (cuerr != cudaSuccess)
    {
        fprintf(stderr, "Cannot allocate device array for a: %s\n",
            cudaGetErrorString(cuerr));
        return 0;
    }

    int* dev_b = NULL;
    cuerr = cudaMalloc((void**)&dev_b, n2b);
    if (cuerr != cudaSuccess)
    {
        fprintf(stderr, "Cannot allocate device array for b: %s\n",
            cudaGetErrorString(cuerr));
        return 0;
    }

    int* dev_c = NULL;
    cuerr = cudaMalloc((void**)&dev_c, n2b);
    if (cuerr != cudaSuccess)
    {
        fprintf(stderr, "Cannot allocate device array for c: %s\n",
            cudaGetErrorString(cuerr));
        return 0;
    }

    // �������� ������������ �������
    cudaEvent_t start, stop;
    float gpuTime = 0.0f;
    cuerr = cudaEventCreate(&start);
    if (cuerr != cudaSuccess)
    {
        fprintf(stderr, "Cannot create CUDA start event: %s\n",
            cudaGetErrorString(cuerr));
        return 0;
    }

    cuerr = cudaEventCreate(&stop);
    if (cuerr != cudaSuccess)
    {
        fprintf(stderr, "Cannot create CUDA end event: %s\n",
            cudaGetErrorString(cuerr));
        return 0;
    }

    // ����������� ������ � ����� �� ������
    cuerr = cudaMemcpy(dev_a, a, n2b, cudaMemcpyHostToDevice);
    if (cuerr != cudaSuccess)
    {
        fprintf(stderr, "Cannot copy a array from host to device: %s\n",
            cudaGetErrorString(cuerr));
        return 0;
    }

    cuerr = cudaMemcpy(dev_b, b, n2b, cudaMemcpyHostToDevice);
    if (cuerr != cudaSuccess)
    {
        fprintf(stderr, "Cannot copy b array from host to device: %s\n",
            cudaGetErrorString(cuerr));
        return 0;
    }

    // ��������� ����� ������
    cuerr = cudaEventRecord(start, 0);
    if (cuerr != cudaSuccess)
    {
        fprintf(stderr, "Cannot record CUDA event: %s\n",
            cudaGetErrorString(cuerr));
        return 0;
    }

    //������ ����
    int BLOCK_NUMBER = (n + BLOCK_SIZE - 1) / BLOCK_SIZE;
    kernel <<< BLOCK_NUMBER, BLOCK_SIZE >>> (dev_c, dev_a, dev_b, n);

    cuerr = cudaGetLastError();
    if (cuerr != cudaSuccess)
    {
        fprintf(stderr, "Cannot launch CUDA kernel: %s\n",
            cudaGetErrorString(cuerr));
        return 0;
    }

    // ������������� ���������
    cuerr = cudaDeviceSynchronize();
    if (cuerr != cudaSuccess)
    {
        fprintf(stderr, "Cannot synchronize CUDA kernel: %s\n",
            cudaGetErrorString(cuerr));
        return 0;
    }

    // ��������� ����� ���������
    cuerr = cudaEventRecord(stop, 0);
    if (cuerr != cudaSuccess)
    {
        fprintf(stderr, "Cannot copy c array from device to host: %s\n",
            cudaGetErrorString(cuerr));
        return 0;
    }

    // ����������� ���������� �� ����
    cuerr = cudaMemcpy(c, dev_c, n2b, cudaMemcpyDeviceToHost);
    if (cuerr != cudaSuccess)
    {
        fprintf(stderr, "Cannot copy c array from device to host: %s\n",
            cudaGetErrorString(cuerr));
        return 0;
    }

    // ������ �������
    cuerr = cudaEventElapsedTime(&gpuTime, start, stop);
    printf("time spent executing %s: %.9f seconds\n", "kernel", gpuTime / 1000);

    printf("The last 10 elements: ");
    for (int i = 0; i < 10; ++i) {
        printf("%d ", c[i]);
    }



    cudaEventDestroy(start);
    cudaEventDestroy(stop);
    cudaFree(dev_a);
    cudaFree(dev_b);
    cudaFree(dev_c);
    free(a);
    free(b);
    free(c);

    return 0;
}
