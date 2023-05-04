#include <stdio.h>
#include <stdlib.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

/*
len = 4
tid = 0 => startidx = 0
tid = 1 => startidx = 0 + 4 = 4 = 4 - 0
tid = 2 => startidx = 0 + 4 + 3 = 7 = 4*2 - 1
tid = 3 => startidx = 0 + 4 + 3 + 2 = 9 = 4*3 - 3
*/

//<<<1, len(string)>>>
__global__ void stringKernel(char *word, char *result){
    int tid = threadIdx.x; 
    int len = blockDim.x; 
    int start = (tid * len) - (tid * (tid - 1))/2;
    for(int i = 0; i < len - tid; i++)
        result[i + start] = word[i];
}

int main(){
    char *word, *result, *d_word, *d_result;
    int len; 

    printf("Enter word length: ");
    scanf("%d", &len);

    word = (char *)malloc(len*sizeof(char));
    result = (char *)malloc((len * (len+1)/2)*sizeof(char));

    printf("Enter string: ");
    scanf("%s", word);

    cudaMalloc((void **)&d_word, len * sizeof(char));
    cudaMalloc((void **)&d_result, (len * (len+1)/2)*sizeof(char));

    cudaMemcpy(d_word, word, len*sizeof(char), cudaMemcpyHostToDevice);

    stringKernel <<<1, len>>> (d_word, d_result);

    cudaMemcpy(result, d_result, (len * (len+1)/2)*sizeof(char), cudaMemcpyDeviceToHost);

    printf("Resultant string: ");
    for(int i = 0; i < (len * (len+1)/2); i++)
        printf("%c ", result[i]);

    cudaFree(d_word);
    cudaFree(d_result);

    return 0; 
}