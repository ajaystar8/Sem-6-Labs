#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
__global__ void change(char *a,char *b,int size)
{
	int tid=threadIdx.x;
    int start = 0;
    for (int i = 0; i < tid; i++)
        start += size-i;
    for(int i=0;i<size-tid;i++)
        b[start++]=a[i];
}
int main(void)
{
	char a[100],b[100];
	char *d_a,*d_b;
	printf("Enter string: ");
	scanf("%[^\n]%*c",a);
	int n1=strlen(a);
	int size1=n1*sizeof(char);
    int n2=n1;
    for(int i=n1;i>0;i--)
        n2+=i;    
    int size2=n2*sizeof(char);    
	cudaMalloc((void **)&d_a,size1);
	cudaMalloc((void **)&d_b,size2);
	cudaMemcpy(d_a,a,size1,cudaMemcpyHostToDevice);
	change<<<1,n1>>>(d_a,d_b,size1);
	cudaMemcpy(b,d_b,size2,cudaMemcpyDeviceToHost);
	printf("Result: %s\n",b);	
	cudaFree(d_a);
	cudaFree(d_b);
	return 0;
}