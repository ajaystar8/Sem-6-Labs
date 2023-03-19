#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, n, nums[100], subarr[100], res[100], final_res[100], numspp, odd_cnt = 0, even_cnt = 0, fin_odd_cnt, fin_even_cnt;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter number of numbers: \n");
        scanf("%d", &n);
        printf("Enter %d numbers: \n", n);
        for (int i = 0; i < n; i++)
            scanf("%d", &nums[i]);
        numspp = n / size;
    }
    MPI_Bcast(&numspp, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(nums, numspp, MPI_INT, subarr, numspp, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < numspp; i++)
    {
        if (subarr[i] % 2)
        {
            res[i] = 0;
            odd_cnt++;
        }
        else
        {
            res[i] = 1;
            even_cnt++;
        }
    }

    MPI_Gather(res, numspp, MPI_INT, final_res, numspp, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Reduce(&odd_cnt, &fin_odd_cnt, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&even_cnt, &fin_even_cnt, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        for (int i = 0; i < n; i++)
            printf("%d ", final_res[i]);
        printf("\nOdd count = %d\n", fin_odd_cnt);
        printf("Even count = %d\n", fin_even_cnt);
    }

    MPI_Finalize();
    return 0;
}