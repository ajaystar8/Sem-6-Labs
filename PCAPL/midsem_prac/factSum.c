#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, nums[100], num, fact = 1, sum_fact;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter %d numbers: \n", size);
        for (int i = 0; i < size; i++)
            scanf("%d", &nums[i]);
    }
    MPI_Scatter(nums, 1, MPI_INT, &num, 1, MPI_INT, 0, MPI_COMM_WORLD);

    while (num)
    {
        fact *= num;
        num -= 1;
    }

    MPI_Reduce(&fact, &sum_fact, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
        printf("Sum of all factorials: %d\n", sum_fact);

    MPI_Finalize();
    return 0;
}