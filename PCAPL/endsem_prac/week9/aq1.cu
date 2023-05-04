#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>

// n,m
__global__ void kernelOperation(int *d_a, int *d_b, int m, int n){
    int cid = threadIdx.x;
    int rid = threadIdx.y;
    if(rid < m && cid < n){
        int elem = d_a[rid*n + cid];
        if(elem % 2){
            // odd number
            // col sum
            int sum = 0; 
            for(int k = 0; k < m; k++) 
                sum += d_a[k * n + cid];
            d_b[rid*n + cid] = sum;
        }
        else{
            // even number
            // row sum
            int sum = 0; 
            for(int k = 0; k < n; k++) 
                sum += d_a[rid * n + k];
            d_b[rid * n + cid] = sum;
        }
    }
}

int main(){
    int *a, *d_a, *b, *d_b, m, n;
    
    printf("Enter m: ");
    scanf("%d", &m); 

    printf("Enter n: ");
    scanf("%d", &n);

    int size = m*n*sizeof(int);

    a = (int *)malloc(size);
    b = (int *)malloc(size);

    printf("Enter the input matrix: ");
    for(int i = 0; i < m*n; i++)
        scanf("%d", &a[i]);
    
    cudaMalloc((void **)&d_a, size);
    cudaMalloc((void **)&d_b, size);

    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);

    dim3 dimBlock(n,m,1);
    kernelOperation <<<1, dimBlock>>> (d_a, d_b, m, n);

    cudaMemcpy(b, d_b, size, cudaMemcpyDeviceToHost);

    printf("Resultant Matrix: \n");

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++)
            printf("%d\t", b[i*n + j]); 
        printf("\n");
    }

    return 0; 
}