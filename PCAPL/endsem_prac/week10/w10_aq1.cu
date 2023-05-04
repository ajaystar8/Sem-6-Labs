#include <stdio.h>
#include <stdlib.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

// n,m,1
__global__ void matrixOperation(int *d_a, int *d_b, int m, int n){
    int rid = threadIdx.y;
    int cid = threadIdx.x;
    int sum = 0;
    if(rid < m && cid < n){
        for(int k = 0; k < n; k++)
            sum += d_a[rid * n + k];
        for(int k = 0; k < m; k++)
            sum += d_a[k * n + cid];
        sum -= d_a[rid * n + cid];
    }
    d_b[rid * n + cid] = sum;
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
    matrixOperation <<<1, dimBlock>>> (d_a, d_b, m, n);

    cudaMemcpy(b, d_b, size, cudaMemcpyDeviceToHost);

    printf("Resultant Matrix: \n");

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++)
            printf("%d\t", b[i*n + j]); 
        printf("\n");
    }

    return 0; 
}

