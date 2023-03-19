#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, *arr, *subarr, m;
    float sum;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter the value of m: \n");
        scanf("%d", &m);
        arr = (int *)malloc(size * m * sizeof(int));
        printf("Enter %d number(s): \n", size * m);
        for (int i = 0; i < size * m; i++)
            scanf("%d", &arr[i]);
    }
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);

    float avg = 0.0;
    subarr = (int *)malloc(m * sizeof(int));

    MPI_Scatter(arr, m, MPI_INT, subarr, m, MPI_INT, 0, MPI_COMM_WORLD);
    for (int i = 0; i < m; i++)
        avg += subarr[i];
    avg /= m;

    MPI_Reduce(&avg, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("The grand average is: %f\n", sum / size);
    }

    MPI_Finalize();
    return 0;
}