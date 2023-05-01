#include <stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdlib.h>

/// check start

__global__ void matrixMulRow(int *d_mat1, int *d_mat2, int *d_ans, int m1, int n1, int m2, int n2) {
	int tid=blockIdx.x;
    int sum = 0;
    for(int j=0; j<m1; j++) {
        for(int i=0; i<n1; i++) {
            sum += d_mat1[tid*n1+i] * d_mat2[j+n2*i];
        }
        d_ans[tid*m1+j] = sum;
        sum = 0;
    }
}

// work on second row  2 3 3 2 1 2 3 4 5 6
__global__ void matrixMulCol(int *d_mat1, int *d_mat2, int *d_ans, int m1, int n1, int m2, int n2) {
	int tid=blockIdx.x;
    int sum = 0;
    for(int j=0; j<m1; j++) {
        for(int i=0; i<m2; i++) {
            sum += d_mat1[j*m2+i] * d_mat2[tid+n2*i];
            if(tid == 0) {
                printf("%d - %d\n", d_mat1[j*m2+i], d_mat2[tid+n2*i]);
            }
        }
        d_ans[tid+n1*j] = sum;
        sum = 0;
    }
}

// __global__ void matrixMulEle(int *d_mat1, int *d_mat2, int *d_ans, int m1, int n1, int m2, int n2) {
// 	int tid=blockIdx.x;
//     int row = tid/n1, col = tid%n2;
//     int sum = 0;
// 	for(int i=0; i<n1; i++)
//         sum += d_mat1[n1*row+i] * d_mat2[n1*i+col];
//     d_ans[tid] = sum;
// }

/// check end

int main(void) {
	int m1, n1, m2, n2;

	printf("Enter the row and col size of the matrix: ");
	scanf("%d %d %d %d", &m1, &n1, &m2, &n2);

    if(n1 != m2) {
        printf("Matrices are not compatible for multiplication.\n");
        exit(0);
    }


	int *mat1, *mat2, *ans;
	int *d_mat1, *d_mat2, *d_ans;

	mat1 = (int*)malloc(m1*n1*sizeof(int));
	mat2 = (int*)malloc(m2*n2*sizeof(int));
	ans = (int*)malloc(m1*n2*sizeof(int));

	cudaMalloc((void **)&d_mat1, m1*n1*sizeof(int));
	cudaMalloc((void **)&d_mat2, m2*n2*sizeof(int));
	cudaMalloc((void **)&d_ans, m1*n2*sizeof(int));

    printf("Enter the elements of the matrix1: ");
		for(int i=0; i<m1*n1; i++)
			scanf("%d", &mat1[i]);
	printf("Enter the elements of the matrix2: ");
		for(int i=0; i<m2*n2; i++)
			scanf("%d", &mat2[i]);

	cudaMemcpy(d_mat1, mat1, m1*n1*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(d_mat2, mat2, m2*n2*sizeof(int), cudaMemcpyHostToDevice);

    /// check start

	// matrixMulRow<<<m1, 1>>>(d_mat1, d_mat2, d_ans, m1, n1, m2, n2);

	// cudaMemcpy(ans, d_ans, m1*n2*sizeof(int), cudaMemcpyDeviceToHost);
	
	// printf("Final matrix is:\n");
	// for(int i=0; i<m1*n2; i++) {
	// 	if(i%n2 == 0)
	// 		printf("\n");
	// 	printf("%d ", ans[i]);
	// }

	matrixMulCol<<<m1, 1>>>(d_mat1, d_mat2, d_ans, m1, n1, m2, n2);

	cudaMemcpy(ans, d_ans, m1*n2*sizeof(int), cudaMemcpyDeviceToHost);
	
	printf("Final matrix is:\n");
	for(int i=0; i<m1*n2; i++) {
		if(i%n2 == 0)
			printf("\n");
		printf("%d ", ans[i]);
	}

	// matrixMulEle<<<m1*n2, 1>>>(d_mat1, d_mat2, d_ans, m1, n1, m2, n2);

	// cudaMemcpy(ans, d_ans, m1*n2*sizeof(int), cudaMemcpyDeviceToHost);
	
	// printf("Final matrix is:\n");
	// for(int i=0; i<m1*n2; i++) {
	// 	if(i%n2 == 0)
	// 		printf("\n");
	// 	printf("%d ", ans[i]);
	// }
	
	cudaFree(d_mat1);
	cudaFree(d_mat2);
	cudaFree(d_ans);

    /// check end

	return 0;
}