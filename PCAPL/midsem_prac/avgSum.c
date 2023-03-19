#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank, size, m, arr[100], subarr[100];
    float subavg = 0, avg = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        printf("Enter the value of m: \n");
        scanf("%d", &m);
        printf("Enter %d elements: \n", m * size);
        for (int i = 0; i < m * size; i++)
            scanf("%d", &arr[i]);
    }
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(arr, m, MPI_INT, subarr, m, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < m; i++)
        subavg += subarr[i];
    subavg /= m;

    MPI_Reduce(&subavg, &avg, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
        printf("The grand average is : %0.2f\n", avg / size);

    MPI_Finalize();
    return 0;
}