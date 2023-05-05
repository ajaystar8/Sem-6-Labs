#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cuda_runtime.h>

__global__ void leftRotate(char *d_word, char *d_ans, int index, int len) {
    int tid = (blockIdx.x*blockDim.x*blockDim.y) + (blockDim.x*threadIdx.y) + threadIdx.x;
    if((tid<len) && d_word[tid] == ' ') d_ans[tid] = ' ';
    else if((tid<len) && tid == 0 || (tid>0 && d_word[tid-1] == ' ')) {
        int end = tid;
        while((end < (len-1)) && (d_word[end+1] != ' ')) end++;
        int lenofword = end - tid + 1;
        for(int i=tid; i<=end; i++)
            d_ans[((i-tid-index+lenofword)%lenofword)+tid] = d_word[i];
    }
}

__global__ void rightRotate(char *d_word, char *d_ans, int index, int len) {
    int tid = (blockIdx.x*blockDim.x*blockDim.y) + (blockDim.x*threadIdx.y) + threadIdx.x;
    if((tid<len) && d_word[tid] == ' ') d_ans[tid] = ' ';
    else if((tid<len) && tid == 0 || (tid>0 && d_word[tid-1] == ' ')) {
        int end = tid;
        while((end < (len-1)) && (d_word[end+1] != ' ')) end++;
        int lenofword = end - tid + 1;
        for(int i=tid; i<=end; i++)
            d_ans[((i-tid+index)%lenofword)+tid] = d_word[i];
    }
}

int main() {
    char h_word[100], *h_ans;
    char *d_word, *d_ans;

    int index;
    int now = 0, maxlen = 0;

    printf("Enter the word: ");
    scanf("%[^\n]s", h_word);
    printf("Enter the index: ");
    scanf("%d", &index);

    int len = strlen(h_word);

    int templen = 0;
    for(int i=0; i<len; i++) {
        if(i==0 || h_word[i] == ' ') now++;
        if(h_word[i] != ' ') templen++;
        else {
            if(maxlen < templen) maxlen = templen;
            templen = 0;
        }
    }
    
    h_ans = (char*)malloc(len*sizeof(char));

    cudaMalloc((void**)&d_word, len*sizeof(char));
    cudaMalloc((void**)&d_ans, len*sizeof(char));

    dim3 dimGrid(now, 1, 1);
    dim3 dimBlock(4, 2, 1);

    cudaMemcpy(d_word, h_word, len*sizeof(char), cudaMemcpyHostToDevice);

    rightRotate<<<dimGrid, dimBlock>>>(d_word, d_ans, index, len);

    cudaMemcpy(h_ans, d_ans, len*sizeof(char), cudaMemcpyDeviceToHost);

    printf("The final string after right rotation is: %s\n", h_ans);

    leftRotate<<<1, len>>>(d_word, d_ans, index, len);

    cudaMemcpy(h_ans, d_ans, len*sizeof(char), cudaMemcpyDeviceToHost);

    printf("The final string after left rotation is: %s\n", h_ans);
    
    return 0;
}