#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, nums[4][4], subarr[4], sumarr[4], resnums[4][4];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter elements of 4x4 matrix: \n");
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                scanf("%d", &nums[i][j]);
    }
    MPI_Scatter(nums[rank], 4, MPI_INT, subarr, 4, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scan(subarr, sumarr, 4, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    MPI_Gather(sumarr, 4, MPI_INT, resnums[rank], 4, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("New 4x4 matrix is: \n");
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
                printf("%d ", resnums[i][j]);
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}