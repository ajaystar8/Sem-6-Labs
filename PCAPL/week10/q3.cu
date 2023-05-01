#include <stdio.h>
#include <cuda_runtime.h>
#include <math.h>

__global__ void border(int *dArr, int m, int n) {
    int row = blockIdx.x / n;
    int col = blockIdx.x % n;
    if(row > 0 && row < m-1 && col > 0 && col < n-1) {
        int n = 1;
        while(pow(2, n) < dArr[blockIdx.x]) n++;
        if(pow(2, n) == dArr[blockIdx.x]) n++;
        int a[10] ,num , i;
        num = pow(2, n) - 1 - dArr[blockIdx.x];
        for(i=0;num>0;i++) {
            a[i]=num%2;
            num=num/2;
        }
        int ans = 0;
        for(i=i-1;i>=0;i--)
            ans=(ans*10)+a[i];
        dArr[blockIdx.x] = ans;
    }
}

int main() {
    int m, n;
    printf("Enter the dimensions of the matrix: ");
    scanf("%d %d", &m, &n);
    int arr[m*n];
    int *dArr;
    printf("Enter the elements of the matrix: ");
    for(int i=0; i<m*n; i++)
        scanf("%d", &arr[i]);
    cudaMalloc(&dArr, m*n*sizeof(int));
    cudaMemcpy(dArr, arr, m*n*sizeof(int), cudaMemcpyHostToDevice);
    border<<<m*n, 1>>>(dArr, m, n);
    cudaMemcpy(arr, dArr, m*n*sizeof(int), cudaMemcpyDeviceToHost);
    printf("Matrix:\n");
    for(int i=0; i<m*n; i++) {
        if(i%n == 0) printf("\n");
        printf("%d ", arr[i]);
    }
    cudaFree(dArr);
    return 0;
}