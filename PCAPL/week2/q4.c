#include "mpi.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int rank, size, n;
    int arr[100] = {0}; 
    char word[100]; 
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        printf("Enter an integer: ");
        scanf("%d", &n);
        MPI_Send(&n, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&n, 1, MPI_INT, size-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Value recieved is %d\n", n);
    }
    else{
        MPI_Recv(&n, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Value recieved is %d\n", n);
        n++;
        MPI_Send(&n, 1, MPI_INT, (rank+1) % (size), 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0; 
}