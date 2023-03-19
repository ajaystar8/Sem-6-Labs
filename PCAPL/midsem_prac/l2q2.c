#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, nums[100], num;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter %d numbers: \n", size);
        for (int i = 0; i < size; i++)
            scanf("%d", &nums[i]);
        for (int i = 0; i < size; i++)
            MPI_Send(&nums[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
    }
    // MPI_Scatter(nums, 1, MPI_INT, &num, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Recv(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Number recieved: %d\n", num);

    MPI_Finalize();
    return 0;
}