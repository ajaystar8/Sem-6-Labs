#include <stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void matrixAddRow(int *d_mat1, int *d_mat2, int *d_ans, int m, int n) {
	int tid=blockIdx.x;
	for(int i=0; i<n; i++)
		d_ans[tid*n+i] = d_mat1[tid*n+i] + d_mat2[tid*n+i];
}

__global__ void matrixAddCol(int *d_mat1, int *d_mat2, int *d_ans, int m, int n) {
	int tid=blockIdx.x;
	for(int i=0; i<n; i++)
		d_ans[tid+n*i] = d_mat1[tid+n*i] + d_mat2[tid+n*i];
}

__global__ void matrixAddEle(int *d_mat1, int *d_mat2, int *d_ans, int m, int n) {
	int tid=blockIdx.x;
	d_ans[tid] = d_mat1[tid] + d_mat2[tid];
}

int main(void) {
	int m, n;

	printf("Enter the row and col size of the matrix: ");
	scanf("%d %d", &m, &n);

	int *mat1, *mat2, *ans;
	int *d_mat1, *d_mat2, *d_ans;

	mat1 = (int*)malloc(m*n*sizeof(int));
	mat2 = (int*)malloc(m*n*sizeof(int));
	ans = (int*)malloc(m*n*sizeof(int));

	cudaMalloc((void **)&d_mat1, m*n*sizeof(int));
	cudaMalloc((void **)&d_mat2, m*n*sizeof(int));
	cudaMalloc((void **)&d_ans, m*n*sizeof(int));

    printf("Enter the elements of the matrix1: ");
		for(int i=0; i<m*n; i++)
			scanf("%d", &mat1[i]);
	printf("Enter the elements of the matrix2: ");
		for(int i=0; i<m*n; i++)
			scanf("%d", &mat2[i]);

	cudaMemcpy(d_mat1, mat1, m*n*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(d_mat2, mat2, m*n*sizeof(int), cudaMemcpyHostToDevice);

	matrixAddRow<<<m, 1>>>(d_mat1, d_mat2, d_ans, m, n);

	cudaMemcpy(ans, d_ans, m*n*sizeof(int), cudaMemcpyDeviceToHost);
	
	printf("Final matrix is:\n");
	for(int i=0; i<m*n; i++) {
		if(i%n == 0)
			printf("\n");
		printf("%d ", ans[i]);
	}

	matrixAddCol<<<m, 1>>>(d_mat1, d_mat2, d_ans, m, n);

	cudaMemcpy(ans, d_ans, m*n*sizeof(int), cudaMemcpyDeviceToHost);
	
	printf("Final matrix is:\n");
	for(int i=0; i<m*n; i++) {
		if(i%n == 0)
			printf("\n");
		printf("%d ", ans[i]);
	}

	matrixAddEle<<<m*n, 1>>>(d_mat1, d_mat2, d_ans, m, n);

	cudaMemcpy(ans, d_ans, m*n*sizeof(int), cudaMemcpyDeviceToHost);
	
	printf("Final matrix is:\n");
	for(int i=0; i<m*n; i++) {
		if(i%n == 0)
			printf("\n");
		printf("%d ", ans[i]);
	}
	
	cudaFree(d_mat1);
	cudaFree(d_mat2);
	cudaFree(d_ans);

	return 0;
}
