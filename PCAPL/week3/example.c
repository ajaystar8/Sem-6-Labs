#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]){
    int rank, size, N, A[10], B[10], c;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        N = size; 
        printf("Enter %d values: ", N);
        for(int i = 0; i < N; i++)
            scanf("%d", &A[i]);
    }
    MPI_Scatter(A, 1, MPI_INT, &c, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("I have recieved %d in process %d\n", c, rank);

    c *= c;

    MPI_Gather(&c, 1, MPI_INT, B, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0){
        printf("The result gathered in root is: ");
        for(int i = 0; i < N; i++)
            printf("%d ", B[i]);
    }

    MPI_Finalize();
    return 0; 
}