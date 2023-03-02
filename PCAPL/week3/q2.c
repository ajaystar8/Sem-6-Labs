#include "mpi.h"
#include <stdio.h>

float average(float arr[100], int m){
    float average = 0; 
    for(int i = 0; i < m; i++)
        average += arr[i];
    return average/m;
}

int main(int argc, char *argv[]){
    int rank, size, m, N; 
    float avg, A[100], B[100], T[100];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        N = size;
        printf("Enter the value of M: ");
        scanf("%d", &m);

        printf("Enter %d elements: ", m*N);
        for(int i = 0; i < (m*N); i++)
            scanf("%f", &A[i]);
    }
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(A, m, MPI_FLOAT, T, m, MPI_FLOAT, 0, MPI_COMM_WORLD);
    avg = average(T, m);
    MPI_Gather(&avg, 1, MPI_FLOAT, B, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    if(rank == 0){
        float final_avg = average(B, size);
        printf("The final average of values is: %0.2f\n", final_avg);
    }

    MPI_Finalize();
    return 0; 

}