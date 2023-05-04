#include<stdio.h>
#include<stdlib.h>
#include<string.h>

__global__ void copyKernel(char *word, char *result){
    int len = blockDim.x;
    int tid = threadIdx.x;
    int start = (tid*len)-(((tid-1)*tid)/2);
    for(int i = 0; i < len-tid; i++) result[start+i] = word[i];
}

int main(){

    char word[100];
    printf("Enter word : ");
    scanf("%s", word);
    int len = strlen(word);
    int reslen = (len*(len+1))/2;
    char *result = (char*)malloc((reslen+1)*sizeof(char));

    char *d_word, *d_result;
    cudaMalloc((void**)&d_word, (len+1)*sizeof(char));
    cudaMalloc((void**)&d_result, (reslen+1)*sizeof(char));

    cudaMemcpy(d_word, word, len*sizeof(char), cudaMemcpyHostToDevice);
    copyKernel<<<1, len>>>(d_word, d_result);

    cudaMemcpy(result, d_result, reslen*sizeof(char), cudaMemcpyDeviceToHost);

    printf("Result : %s\n", result);

    return 0;
}