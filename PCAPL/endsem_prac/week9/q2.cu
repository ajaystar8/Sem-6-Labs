#include <stdio.h>
#include <stdlib.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void mulRow(int *d_a, int *d_b, int *d_c, int wa, int wb){
    int rid = threadIdx.x; 
    int sum = 0; 
    for(int cidB = 0; cidB < wb; cidB++){
        sum = 0; 
        for(int k = 0; k < wa; k++)
            sum += d_a[rid*wa + k] * d_b[k*wb + cidB];
        d_c[rid*wb + cidB] = sum; 
    }
}

__global__ void mulColumn(int *d_a, int *d_b, int *d_c, int ha, int wa){
    int cidB = threadIdx.x; 
    int sum = 0; 
    int wb = blockDim.x; 
    for(int ridA = 0; ridA < ha; ridA++){
        sum = 0; 
        for(int k = 0; k < wa; k++)
            sum += d_a[ridA * wa + k] * d_b[k * wb + cidB];
        d_c[ridA*wb + cidB] = sum; 
    }
}

__global__ void mulElement(int *d_a, int *d_b, int *d_c, int wa){
    int ridA = threadIdx.y;
    int cidB = threadIdx.x;
    int wb = blockDim.x; 
    int sum = 0; 
    for(int k = 0; k < wa; k++)
        sum += d_a[ridA * wa + k] * d_b[k * wb + cidB];
    d_c[ridA * wb + cidB] = sum; 
}

int main(){
    int *a, *b, *c, ha, wa, hb, wb; 
    int *d_a, *d_b, *d_c; 

    printf("Enter ha: ");
    scanf("%d", &ha);

    printf("Enter wa: ");
    scanf("%d", &wa);

    printf("Enter hb: ");
    scanf("%d", &hb);

    printf("Enter wb: ");
    scanf("%d", &wb);

    int size1 = ha * wa * sizeof(int);
    int size2 = hb * wb * sizeof(int);
    int ressize = ha * wb * sizeof(int);

    // allocate host memory
    a = (int *)malloc(size1);
    b = (int *)malloc(size2);
    c = (int *)malloc(ressize);

    // take input for matrices
    printf("Enter the elements of Matrix-A: ");
    for(int i = 0; i < ha*wa; i++)
        scanf("%d", &a[i]);
    
    printf("Enter the elements of Matrix-B: ");
    for(int i = 0; i < hb*wb; i++)
        scanf("%d", &b[i]);

    // allocate device memory
    cudaMalloc((void **)&d_a, size1);
    cudaMalloc((void **)&d_b, size2);
    cudaMalloc((void **)&d_c, ressize);

    // send host memory to device
    cudaMemcpy(d_a, a, size1, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size2, cudaMemcpyHostToDevice);

    // // launch kernel
    // mulRow <<< 1, ha >>> (d_a, d_b, d_c, wa, wb);

    // // send results to host
    // cudaMemcpy(c, d_c, ressize, cudaMemcpyDeviceToHost);

    // // display results
    // printf("Resultant matrix -mulRow: \n");

    // for(int i = 0; i < ha; i++){
    //     for(int j = 0; j < wb; j++)
    //         printf("%d\t", c[i*ha + j]); 
    //     printf("\n");
    // }

    // // launch kernel
    // mulColumn <<< 1, wb >>> (d_a, d_b, d_c, ha, wa);

    // // send results to host
    // cudaMemcpy(c, d_c, ressize, cudaMemcpyDeviceToHost);

    // // display results
    // printf("Resultant matrix - mulColumn: \n");

    // for(int i = 0; i < ha; i++){
    //     for(int j = 0; j < wb; j++)
    //         printf("%d\t", c[i*ha + j]); 
    //     printf("\n");
    // }

    // launch kernel
    dim3 block_size(wb, ha);
    mulElement <<< 1, block_size >>> (d_a, d_b, d_c, wa);


    // send results to host
    cudaMemcpy(c, d_c, ressize, cudaMemcpyDeviceToHost);

    // display results
    printf("Resultant matrix - mulElement: \n");

    for(int i = 0; i < ha; i++){
        for(int j = 0; j < wb; j++)
            printf("%d\t", c[i*ha + j]); 
        printf("\n");
    }

    // release memory
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    return 0; 

}