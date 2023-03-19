#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, n, sendVal, factSum, totalSum;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter the value of n: \n");
        scanf("%d", &n);
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    sendVal = rank + 1;
    MPI_Scan(&sendVal, &factSum, 1, MPI_INT, MPI_PROD, MPI_COMM_WORLD);
    MPI_Scan(&factSum, &totalSum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    printf("The sum of factorials uptill now: %d\n", totalSum);

    MPI_Finalize();
    return 0;
}