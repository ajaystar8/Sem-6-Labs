#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, n, nums[100], subnums[100], res[100], numspp, odd = 0, even = 0, final_res[100], final_odd, final_even;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter total numbers: \n");
        scanf("%d", &n);
        printf("Enter %d numbers: \n", n);
        for (int i = 0; i < n; i++)
            scanf("%d", &nums[i]);
        numspp = n / size;
    }
    MPI_Bcast(&numspp, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(nums, numspp, MPI_INT, subnums, numspp, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < numspp; i++)
    {
        if (subnums[i] % 2)
        {
            odd++;
            res[i] = 0;
        }
        else
        {
            even++;
            res[i] = 1;
        }
    }

    MPI_Gather(res, numspp, MPI_INT, final_res, numspp, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Reduce(&odd, &final_odd, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&even, &final_even, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        for (int i = 0; i < n; i++)
            printf("%d ", final_res[i]);
        printf("\nEven (count) = %d\n", final_even);
        printf("Odd (count) = %d\n", final_odd);
    }

    MPI_Finalize();
    return 0;
}