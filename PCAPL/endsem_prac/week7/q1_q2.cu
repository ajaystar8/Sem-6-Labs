#include <stdio.h> 
#include <stdlib.h> 
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

// // <<< N, 1 >>>
// __global__ void vectorSum1(int *a, int *b, int *c){
//     int elemIdx = blockIdx.x; 
//     c[elemIdx] = a[elemIdx] + b[elemIdx];
// }

// // <<< 1, N >>>
// __global__ void vectorSum2(int *a, int *b, int *c){
//     int elemIdx = threadIdx.x; 
//     c[elemIdx] = a[elemIdx] + b[elemIdx];
// }

// <<< ceil(N/256.0,1,1), (256,1,1) >>>
__global__ void vectorSum3(int *a, int *b, int *c, int n){
    int elemIdx = blockIdx.x * blockDim.x + threadIdx.x;
    if(elemIdx < n) 
        c[elemIdx] = a[elemIdx] + b[elemIdx];
}

int main(){
    int *a, *b, *c, *d_a, *d_b, *d_c, n, size;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    size = n * sizeof(int);

    a = (int *)malloc(size);
    b = (int *)malloc(size);
    c = (int *)malloc(size);

    printf("Enter elements of A: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter elements of B: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &b[i]);

    cudaMalloc((void **)&d_a, size);
    cudaMalloc((void **)&d_b, size);
    cudaMalloc((void **)&d_c, size);

    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

    // vectorSum1 <<< n, 1 >>> (d_a, d_b, d_c);

    // cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

    // printf("Result: \n");
    // for(int i = 0; i < n; i++)
    //     printf("%d ", c[i]);

    // vectorSum2 <<< 1, n >>> (d_a, d_b, d_c);

    // cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

    // printf("Result: \n");
    // for(int i = 0; i < n; i++)
    //     printf("%d ", c[i]);

    dim3 dimGrid(ceil(n/256.0), 1, 1);
    dim3 dimBlock(256, 1, 1);
    vectorSum3 <<< dimGrid, dimBlock >>> (d_a, d_b, d_c, n);

    cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

    printf("Result: \n");
    for(int i = 0; i < n; i++)
        printf("%d ", c[i]);

    return 0; 
}