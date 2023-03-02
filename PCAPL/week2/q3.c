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
        printf("Enter values of the array: ");
        for(int i = 0; i < size; i++)
            scanf("%d", &arr[i]);

        int buf_size = MPI_BSEND_OVERHEAD + size; 
        int *buf = (int *)malloc(buf_size * sizeof(int));
        MPI_Buffer_attach(buf, buf_size);
        for(int i = 0; i < size-1; i++)
            MPI_Bsend(&arr[i], 1, MPI_INT, i+1, 0, MPI_COMM_WORLD);
        MPI_Buffer_detach(&buf, &buf_size);
    }
    else{
        if(rank % 2){
            MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Odd ranked process. Cube of number is %d\n", n*n*n);
        }
        else{
            MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Even ranked process. Square of number is %d\n", n*n);
        }
    }
    MPI_Finalize();
    return 0; 
}