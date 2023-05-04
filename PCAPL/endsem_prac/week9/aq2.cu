#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>

// 1, n,m
__global__ void matrixKernel(int *d_a, int *d_b, int n){
    int rid = threadIdx.y; 
    int cid = threadIdx.x; 
    if (rid < n && cid < n){
        if(rid == cid)
            d_b[rid * n + cid] = 0;
        else if(rid > cid){
            // lower traingle
            int sum = 0; 
            int elem = d_a[rid * n + cid];
            while(elem){
                sum += elem % 10; 
                elem /= 10;
            }
            d_b[rid * n + cid] = sum; 
        }
        else{
            // upper traingle
            int fact = 1; 
            int elem = d_a[rid * n + cid];
            while(elem){
                fact *= elem; 
                elem--; 
            }
            d_b[rid * n + cid] = fact; 
        }
    }
}

int main(){
    int *a, *d_a, *b, *d_b, n;
    
    printf("Enter n: ");
    scanf("%d", &n);

    int size = n * n * sizeof(int);

    a = (int *)malloc(size);
    b = (int *)malloc(size);

    printf("Enter the values of the matrix: ");
    for(int i = 0; i < n*n; i++)
        scanf("%d", &a[i]);

    cudaMalloc((void **)&d_a, size);
    cudaMalloc((void **)&d_b, size);

    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);

    dim3 dimBlock(n,n,1);
    kernelOperation <<<1, dimBlock>>> (d_a, d_b, n);

    cudaMemcpy(b, d_b, size, cudaMemcpyDeviceToHost);

    printf("Resultant Matrix: \n");

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            printf("%d\t", b[i*n + j]); 
        printf("\n");
    }

    cudaFree(d_a);
    cudaFree(d_b);

    return 0; 

}