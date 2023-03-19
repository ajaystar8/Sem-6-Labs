#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(int argc, char *argv[])
{
    int rank, size;
    int scat[100];
    int M, arr[100], length;
    int res[100];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter M value : \n");
        scanf("%d", &M);
        printf("\nEnter %d numbers for matrix\n", size * M);
        for (int i = 0; i < M * size; i++)
            scanf("%d", &arr[i]);
    }
    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(arr, M, MPI_INT, scat, M, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < M; i++)
        scat[i] = pow(scat[i], rank + 2);

    MPI_Gather(scat, M, MPI_INT, res, M, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
        for (int i = 0; i < size * M; i++)
            printf("%d ", res[i]);

    MPI_Finalize();

    return 0;
}