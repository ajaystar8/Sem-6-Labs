#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void stringReverse(char *d_string, int len){
    int start = threadIdx.x; 
    if(start == 0 || d_string[start - 1] == ' '){
        int end = start; 
        while(d_string[end + 1] != ' ' && end + 1 != len)
            end++;
        for(int i = start; i <= (end + start)/2; i++){
            char temp = d_string[end + start - i];
            d_string[end + start - i] = d_string[i];
            d_string[i] = temp; 
        }
    }
}

int main(){
    char string[100], *d_string, *result; 

    printf("Enter string: ");
    scanf("%[^\n]s",string);

    int len = strlen(string);

    result = (char *)malloc(len * sizeof(char));

    cudaMalloc((void **)&d_string, len*sizeof(char));

    cudaMemcpy(d_string, string, len*sizeof(char), cudaMemcpyHostToDevice);

    stringReverse <<< 1, len >>> (d_string, len);

    cudaMemcpy(result, d_string, len*sizeof(char), cudaMemcpyDeviceToHost);

    printf("Reversed string: %s\n", result);

    cudaFree(d_string);

    return 0; 
}