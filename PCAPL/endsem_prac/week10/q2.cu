#include <stdio.h>
#include <stdlib.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

// <<<rows, cols>>>
__global__ void rowOperation(int *d_a, int *d_b){
    int rowId = blockIdx.x; 
    int width = blockDim.x;
    int newVal = 1;
    int k = threadIdx.x;
    int power = rowId + 1; 
    while(power){
        newVal *= d_a[rowId * width + k];
        power--;
    }
    d_b[rowId * width + k] = newVal;
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

    rowOperation <<<m, n>>> (d_a, d_b);

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