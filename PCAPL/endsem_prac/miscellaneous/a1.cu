#include<stdio.h>
#include<stdlib.h>

__global__ void matrixKernel(int *matrix, int *result){
    int row = threadIdx.x;
    int col = threadIdx.y;
    int m = blockDim.x;
    int n = blockDim.y;
    int sum = 0;
    for(int i = 0; i < n; i++) sum += matrix[row*n+i];
    for(int i = 0; i < m; i++) sum += matrix[i*n+col];
    result[row*n+col] = sum - matrix[row*n+col];
}

int main(){

    int m, n;
    printf("Enter m and n : ");
    scanf("%d %d", &m, &n);
    int size = m*n*sizeof(int);
    int *matrix = (int*)malloc(size);
    int *result = (int*)malloc(size);
    printf("Enter elements of matrix : \n");
    for(int i = 0; i < m*n; i++) scanf("%d", &matrix[i]);

    int *d_matrix, *d_result;
    cudaMalloc((void**)&d_matrix, size);
    cudaMalloc((void**)&d_result, size);
    cudaMemcpy(d_matrix, matrix, size, cudaMemcpyHostToDevice);

    dim3 dimBlock(m,n,1);
    matrixKernel<<<1, dimBlock>>>(d_matrix, d_result);

    cudaMemcpy(result, d_result, size, cudaMemcpyDeviceToHost);

    printf("Result : ");
    for(int i = 0; i < m; i++){
        printf("\n");
        for(int j = 0; j < n; j++)
            printf("%d ", result[i*n+j]);
    }

    cudaFree(d_matrix);
    cudaFree(d_result);

    return 0;

}