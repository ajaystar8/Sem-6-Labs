#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>

__global__ void transpose(int *d_a, int *d_t){
    int k = threadIdx.x; 
    int row = blockIdx.x;
    int width = blockDim.x;
    int transposed_width = gridDim.x; 

    //in d_t[] -> col = row for a transposed matrix
    d_t[k * transposed_width + row] = d_a[row * width + k];
}

int main(){
    int *a, *t, m, n; 
    int *d_a, *d_t; 

    printf("Enter the value of m: ");
    scanf("%d", &m);

    printf("Enter the value of n: ");
    scanf("%d", &n);

    int size = m*n*sizeof(int);

    // 1. Allocating host memory
    a = (int *)malloc(size);
    t = (int *)malloc(size);

    // 2. Taking input for matrix
    for(int i = 0; i < m*n; i++)
        scanf("%d", &a[i]);

    // 3. Allocating device memory
    cudaMalloc((void **)&d_a, size);
    cudaMalloc((void **)&d_t, size);

    // 4. Sending memory to device
    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);

    // 5. Kernel Launch
    transpose<<<m,n>>>(d_a, d_t);

    // 6. Sending results from device to host
    cudaMemcpy(t, d_t, size, cudaMemcpyDeviceToHost);

    // 7. Display result
    printf("Resultant vector is: \n");

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++)
            printf("%d\t", t[i*m + j]); 
        printf("\n");
    }

    // 8. Free device memory
    cudaFree(d_a);
    cudaFree(d_t);

    return 0; 
}