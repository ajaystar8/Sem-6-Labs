#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char *argv[])
{
    int rank, size, nums[100], num;
    int *buffer;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter %d elements: \n", size);
        for (int i = 0; i < size; i++)
            scanf("%d", &nums[i]);
        int buff_size = size;
        buffer = (int *)malloc(size * sizeof(int));
        MPI_Buffer_attach(buffer, buff_size);
        for (int i = 0; i < size; i++)
            MPI_Bsend(&nums[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        MPI_Buffer_detach(buffer, &buff_size);
    }
    MPI_Recv(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    if (rank % 2)
    {
        num = pow(num, 3);
        printf("Cube of number is: %d\n", num);
    }
    else
    {
        num = pow(num, 2);
        printf("Square of number is: %d\n", num);
    }

    MPI_Finalize();
    return 0;
}