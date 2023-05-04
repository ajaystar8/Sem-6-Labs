#include <stdio.h>
#include <stdlib.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void doOperation(int *d_a, int *d_b, int m, int n){
    int rowId = blockIdx.x;
    int width = blockDim.x; 
    int k = threadIdx.x;

    if((rowId > 0 && rowId < m - 1) && (k > 0 && k < n -1))
        d_b[rowId * width + k] = 2 * d_a[rowId * width + k];
    else
        d_b[rowId * width + k] = d_a[rowId * width + k];
}

int main(){
    int *a, *b, m, n, size; 
    int *d_a, *d_b;

    printf("Enter m: ");
    scanf("%d", &m);

    printf("Enter n: ");
    scanf("%d", &n);

    size = m * n * sizeof(int);

    a = (int *)malloc(size);
    b = (int *)malloc(size);

    printf("Enter the values of the matrix: ");
    for(int i = 0; i < m*n; i++)
        scanf("%d", &a[i]);

    cudaMalloc((void **)&d_a, size);
    cudaMalloc((void **)&d_b, size);

    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);

    doOperation <<<m, n>>> (d_a, d_b, m, n);

    cudaMemcpy(b, d_b, size, cudaMemcpyDeviceToHost);

    printf("Resultant Matrix: \n");

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++)
            printf("%d\t", b[i*m + j]); 
        printf("\n");
    }

    cudaFree(d_a);
    cudaFree(d_b);

    return 0; 
}