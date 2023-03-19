#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char *argv[])
{
    int rank, size, m, arr[100], subarr[100], res[100], final_res[100];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter the value of m: \n");
        scanf("%d", &m);
        printf("Enter %d numbers: \n", m * size);
        for (int i = 0; i < m * size; i++)
            scanf("%d", &arr[i]);
    }
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(arr, m, MPI_INT, subarr, m, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < m; i++)
        res[i] = pow(subarr[i], rank + 2);

    MPI_Gather(res, m, MPI_INT, final_res, m, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("The final result is: \n");
        for (int i = 0; i < m * size; i++)
            printf("%d ", final_res[i]);
    }

    MPI_Finalize();
    return 0;
}