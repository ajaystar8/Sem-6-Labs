#include <stdio.h>
#include <stdlib.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#define MAX_SENTENCE_LENGTH 100
#define MAX_WORD_LENGTH 10
#define BLOCK_SIZE 128

__global__ void wordMatch(char *d_sentence, char *d_word, int *d_wordCount, int len){
    int tid = threadIdx.x; 
    int i = 0; 
    while(i < blockDim.x && d_word[i] != '\0' && d_sentence[tid + i] == d_word[i])
        i++; 
    if(i == len)
        atomicAdd(d_wordCount, 1);
}

int main() {
    char sentence_h[100], word_h[100];
    int wordCount_h = 0;

    printf("Enter a sentence: ");
    scanf("%[^\n]s",sentence_h);
    printf("Enter a word: ");
    scanf("%s", word_h);

    char* sentence_d;
    char* word_d;
    int* wordCount_d;

    cudaMalloc(&sentence_d, MAX_SENTENCE_LENGTH * sizeof(char));
    cudaMalloc(&word_d, MAX_WORD_LENGTH * sizeof(char));
    cudaMalloc(&wordCount_d, sizeof(int));
    
    cudaMemcpy(sentence_d, sentence_h, MAX_SENTENCE_LENGTH * sizeof(char), cudaMemcpyHostToDevice);
    cudaMemcpy(word_d, word_h, MAX_WORD_LENGTH * sizeof(char), cudaMemcpyHostToDevice);
    cudaMemcpy(wordCount_d, &wordCount_h, sizeof(int), cudaMemcpyHostToDevice);
    
    wordMatch<<< 1 ,strlen(sentence_h)>>>(sentence_d, word_d, wordCount_d, strlen(word_h));

    cudaMemcpy(&wordCount_h, wordCount_d, sizeof(int), cudaMemcpyDeviceToHost);

    printf("The word '%s' appears %d times in the sentence.\n", word_h, wordCount_h);

    cudaFree(sentence_d);
    cudaFree(word_d);
    cudaFree(wordCount_d);

    return 0;

}