#include <stdio.h>
#include <stdlib.h> 
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void addRow(int *d_a, int *d_b, int *d_c){
    int k = threadIdx.x; 
    int width = blockDim.x;
    int row = blockIdx.x; 
    d_c[row*width + k] = d_a[row*width + k] + d_b[row*width + k];
}

__global__ void addColumn(int *d_a, int *d_b, int *d_c){
    int k = threadIdx.x; 
    int width = blockDim.x;
    int col = blockIdx.x;
    
    d_c[k*width + col] = d_a[k*width + col] + d_b[k*width + col];
}

__global__ void addElement(int *d_a, int *d_b, int *d_c){
    int elem = threadIdx.x; 
    d_c[elem] = d_a[elem] + d_b[elem];
}

int main(){
    int *a, *b, *c, m, n, size;
    int *d_a, *d_b, *d_c; 

    printf("Enter the value of m: ");
    scanf("%d", &m);

    printf("Enter the value of n: ");
    scanf("%d", &n);

    size = m*n*sizeof(int);

    // allocate host memory

    a = (int *)malloc(size);
    b = (int *)malloc(size);
    c = (int *)malloc(size);

    // take input to fill matrix

    printf("Enter %d elements of Matrix-A: ", m*n);
    for(int i = 0; i < m*n; i++)
        scanf("%d", &a[i]);

    printf("Enter %d elements of Matrix-B: ", m*n);
    for(int i = 0; i < m*n; i++)
        scanf("%d", &b[i]);

    // allocate device memory

    cudaMalloc((void **)&d_a, size);
    cudaMalloc((void **)&d_b, size);
    cudaMalloc((void **)&d_c, size);

    // transfer memory from host to device
    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

    // launch kernel - 1a
    addRow <<<m, n>>> (d_a, d_b, d_c);

    // transfer memory from device to host
    cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

    // display results

    printf("\nResultant vector by addRow is: \n");

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++)
            printf("%d\t", c[i*m + j]); 
        printf("\n");
    }

    // launch kernel - 1b
    addRow <<<n, m>>> (d_a, d_b, d_c);

    // transfer memory from device to host
    cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

    // display results

    printf("\nResultant vector by addColumn is: \n");

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++)
            printf("%d\t", c[i*m + j]); 
        printf("\n");
    }

    // launch kernel - 1c
    addRow <<<1, m*n>>> (d_a, d_b, d_c);

    // transfer memory from device to host
    cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

    // display results

    printf("\nResultant vector by addElement is: \n");

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++)
            printf("%d\t", c[i*m + j]); 
        printf("\n");
    }

    // release memory
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    return 0; 
}