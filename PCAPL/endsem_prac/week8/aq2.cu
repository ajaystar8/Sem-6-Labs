#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void stringRepeat(char *d_string, char *d_result, int length, int n){
    int tid = threadIdx.x;
    for(int i = 0; i < n; i++){
        int targetIdx = i * length + tid;
        d_result[targetIdx] = d_string[tid];
    }
}

int main(){
    char string[100], *d_string, *result, *d_result; 
    int n; 

    printf("Enter the string: ");
    scanf("%s", string);

    printf("Enter n: ");
    scanf("%d", &n);

    int length = strlen(string);

    int size = length * sizeof(char);
    int res_size = length * n * sizeof(char);

    result = (char *)malloc(res_size);

    cudaMalloc((void **)&d_string, size);
    cudaMalloc((void **)&d_result, res_size);

    cudaMemcpy(d_string, string, size, cudaMemcpyHostToDevice);

    stringRepeat <<< 1, length >>> (d_string, d_result, length, n);

    cudaMemcpy(result, d_result, res_size, cudaMemcpyDeviceToHost);

    printf("New string: %s\n", result);

    cudaFree(d_result);
    cudaFree(d_string);

    return 0; 
}