#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

// <<< 1, length >>>
__global__ void rightRotation(char *string, char *result, int length, int n){
    int tid = threadIdx.x;
    if(tid < length - n)
        result[tid + n] = string[tid];
    else
        result[length - tid - 1] = string[tid];
}

// // <<< 1, length >>>
// __global__ void leftRotation(char *string, char *result, int length, int n){
//     int tid = threadIdx.x;
//     if(tid < n)
//         result[length - n + tid] = string[tid];
//     else
//         result[tid - n] = string[tid];
// }

// <<< 1, (2,2,1) >>>
__global__ void rightRotation2D(char *string, char *result, int length, int n){
    int tid = blockIdx.x * blockDim.x * blockDim.y + threadIdx.y * blockDim.x + threadIdx.x;
    if(tid < length){
        if(string[tid] == ' ') result[tid] = ' ';
        else if((tid == 0) || (tid > 0 && string[tid - 1] == ' ')){
            int end = tid; 
            while(string[end + 1] != ' ' && end < len - 1)
                end++; 
            int wordlen = end - tid + 1; 
            for(int i = tid; i <= end; i++)
                result[]
        }
    }
}

int main(){
    char string[100], temp[100], *d_string, *result, *d_result; 
    int length, n; 

    printf("Enter the string: ");
    scanf("%[^\n]s",string);

    length = strlen(string);

    printf("Enter value of n: ");
    scanf("%d", &n);

    result = (char *)malloc(length*sizeof(char));

    cudaMalloc((void **)&d_string, length*sizeof(char));
    cudaMalloc((void **)&d_result, length*sizeof(char));

    printf("Result: \n");

    for(int i = 0; i < length; i++){
        int j = 0;
        while(string[i] != ' ')
            temp[j++] = string[i++];

        cudaMemcpy(d_string, temp, j*sizeof(char), cudaMemcpyHostToDevice);

        rightRotation <<< 1, j >>> (d_string, d_result, j, n);

        cudaMemcpy(result, d_result, length*sizeof(char), cudaMemcpyDeviceToHost);

        printf("%s\n", result);
    }

    // dim3 dimBlock(2, 2, 1);

    // rightRotation2D <<< 1, dimBlock >>> (d_string, d_result, length, n);

    // cudaMemcpy(result, d_result, length*sizeof(char), cudaMemcpyDeviceToHost);

    // printf("Rotated string: %s\n", result);

    // leftRotation <<< 1, length >>> (d_string, d_result, length, n);

    // cudaMemcpy(result, d_result, length*sizeof(char), cudaMemcpyDeviceToHost);

    // printf("Rotated string: %s\n", result);

    // cudaFree(d_string);
    // cudaFree(d_result);

    return 0; 
}