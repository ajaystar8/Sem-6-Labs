#include <stdio.h>
#include <stdlib.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void stringPatternGenerate(char *d_string, char *d_result){
    int tid = threadIdx.x; 
    int startIdx = tid * (tid + 1) / 2;
    for(int i = 0; i < tid + 1; i++)
        d_result[startIdx + i] = d_string[tid];
}

int main(){
    char string[100], *d_string, *result, *d_result; 

    printf("Enter the string: ");
    scanf("%s", string);

    int length = strlen(string);

    int size = length * sizeof(char);
    int res_size = (length * (length + 1) / 2) * sizeof(char);

    result = (char *)malloc(res_size);

    cudaMalloc((void **)&d_string, size);
    cudaMalloc((void **)&d_result, res_size);

    cudaMemcpy(d_string, string, size, cudaMemcpyHostToDevice);

    stringPatternGenerate <<< 1, length >>> (d_string, d_result);

    cudaMemcpy(result, d_result, res_size, cudaMemcpyDeviceToHost);

    printf("New string: %s\n", result);

    cudaFree(d_result);
    cudaFree(d_string);

    return 0; 
}