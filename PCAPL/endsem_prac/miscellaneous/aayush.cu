#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"device_launch_parameters.h"
#include"cuda_runtime.h"

__global__ void change(char *a, char *b, int size1){
    int tid=threadIdx.x;
    int start = tid * size1 - (tid * (tid -1))/2;
    for(int i=0;i<size1-tid;i++){
        b[start]=a[i];
        start++;
    }
}

int main(void){
    char a[100],b[100];
    printf("Enter the sentence\n");
    scanf("%[^\n]s",a);
    int n1=strlen(a);
    int size1=n1 *sizeof(char);
    int n2 = n1 * (n1 + 1) /2;
    int size2=n2* sizeof(char);

    char *d_a, *d_b;
    cudaMalloc((void**)&d_a, size1);
    cudaMalloc((void**)&d_b,size2);

    cudaMemcpy(d_a,a, size1,cudaMemcpyHostToDevice);
    change<<<1,n1>>>(d_a,d_b,n1);
    cudaMemcpy(b,d_b, size2,cudaMemcpyDeviceToHost);
    printf("The result is %s\n",b);

    return 0; 

}