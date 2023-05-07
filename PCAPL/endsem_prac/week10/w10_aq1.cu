#include <stdio.h>
#include <stdlib.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

// <<< (1,1,1), (n,m,1) >>>
__global__ void kernelOperation(int *d_a, int *d_b, int m, int n){
    int row = threadIdx.y; 
    int col = threadIdx.x; 
    int sum = 0;
    // col sum
    for(int i = 0; i < m; i++)
        sum += d_a[i * n + col];
    // row sum
    for(int i = 0; i < n; i++)
        sum += d_a[row * n + i];
    d_b[row*n + col] = sum;
}

int main(){
    int *a, *b, *d_a, *d_b, m, n, size; 

    printf("Enter m & n: ");
    scanf("%d %d", &m, &n);

    size = m*n*sizeof(int);

    a = (int *)malloc(m*n*sizeof(int));
    b = (int *)malloc(m*n*sizeof(int));

    printf("Enter elements of matrix: ");
    for(int i = 0; i < m*n; i++)
        scanf("%d", &a[i]);

    cudaMalloc((void **)&d_a, size);
    cudaMalloc((void **)&d_b, size);

    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);

    dim3 dimGrid(1,1,1);
    dim3 dimBlock(n,m,1);
    kernelOperation <<<dimGrid, dimBlock>>> (d_a, d_b, m, n);

    cudaMemcpy(b, d_b, size, cudaMemcpyDeviceToHost);

    printf("Resultant Matrix: \n");
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++)
            printf("%d ", b[i*n + j]);
        printf("\n");
    }

    cudaFree(d_a);
    cudaFree(d_b);

    return 0; 
}

/*
1 2 3
4 5 6
*/
