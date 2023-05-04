#include <stdio.h>
#include <stdlib.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void matrixOperation(char *d_letters, int *d_numbers, char *d_output){
    int tid = threadIdx.x;

    int startIdx = 0; 
    for(int i = 0; i < tid; i++)
        startIdx += d_numbers[i];
    
    for(int i = startIdx; i < startIdx + d_numbers[tid]; i++)
        d_output[i] = d_letters[tid];
}

int main(){
    char *d_letters, *output, *d_output; 
    int *d_numbers, m, n;
    char letters[4] = {'a', 'b', 'c', 'd'};
    int numbers[4] = {1, 2, 3, 4};

    printf("Enter m: ");
    scanf("%d", &m); 

    printf("Enter n: ");
    scanf("%d", &n);

    int res_size = 0;
    for(int i = 0; i < m*n; i++)
        res_size += numbers[i];

    output = (char *)malloc(res_size*sizeof(char));

    cudaMalloc((void **)&d_letters, m*n*sizeof(char));
    cudaMalloc((void **)&d_numbers, m*n*sizeof(int));
    cudaMalloc((void **)&d_output, res_size*sizeof(char));

    cudaMemcpy(d_letters, letters, m*n*sizeof(char), cudaMemcpyHostToDevice);
    cudaMemcpy(d_numbers, numbers, m*n*sizeof(int), cudaMemcpyHostToDevice);

    matrixOperation <<<1, m*n>>> (d_letters, d_numbers, d_output);

    cudaMemcpy(output, d_output, res_size*sizeof(char), cudaMemcpyDeviceToHost);

    printf("Resultant string: \n");
    for(int i = 0; i < res_size; i++)
        printf("%c", output[i]);

    cudaFree(d_letters);
    cudaFree(d_numbers);
    cudaFree(d_output);

    return 0; 
}