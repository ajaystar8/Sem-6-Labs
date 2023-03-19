#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int factorial(int n)
{
    int fact = 1;
    while (n)
    {
        fact *= n;
        n -= 1;
    }
    return fact;
}

int main(int argc, char *argv[])
{
    int rank, size, n, sum = 0, final_sum;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter the value of n: \n");
        scanf("%d", &n);
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // 1! + (1 + 2) + 3! + (1 + 2 + 3 + 4) = 20

    if (rank % 2)
        for (int i = 1; i <= rank + 1; i++)
            sum += i;
    else
        sum = factorial(rank + 1);

    MPI_Reduce(&sum, &final_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
        printf("The sum of is: %d\n", final_sum);

    MPI_Finalize();
    return 0;
}