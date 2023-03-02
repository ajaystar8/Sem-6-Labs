#include "mpi.h"
#include <stdio.h>

int factorial(int n){
    if(n == 1)
        return 1; 
    else
        return n * factorial(n-1);
}

int main(int argc, char * argv[]){
    int c, size, rank, A[10], B[10]; 

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        printf("Enter %d numbers: ", size);
        for(int i = 0; i < size; i++)
            scanf("%d", &A[i]);
    }
    MPI_Scatter(A, 1, MPI_INT, &c, 1, MPI_INT, 0, MPI_COMM_WORLD);

    c = factorial(c);

    MPI_Gather(&c, 1, MPI_INT, B, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0){
        int sum = 0; 
        for(int i = 0; i < size; i++)
            sum += B[i];
        printf("The sum of factorials is: %d\n", sum);
    }

    MPI_Finalize();
    return 0; 
}