#include "mpi.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int rank, size, x;
    char word[100]; 
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        printf("Enter value in the master process: ");
        scanf("%d", &x);
        for(int i = 0; i < size-1; i++)
			MPI_Send(&x, 1, MPI_INT, i+1, 0, MPI_COMM_WORLD);
	}

	else {
		MPI_Recv(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Received %d from process 0 in process %d \n", x,rank);
	}
    
    return 0; 
}