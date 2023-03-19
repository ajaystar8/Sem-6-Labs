#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, arr[3][3], target, subarr[3], cnt = 0, final_cnt;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter 9 elements for the 3x3 matrix: \n");
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                scanf("%d", &arr[i][j]);
        printf("Enter element to be searched: \n");
        scanf("%d", &target);
    }
    MPI_Bcast(&target, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(arr, 3, MPI_INT, subarr, 3, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < 3; i++)
        if (subarr[i] == target)
            cnt++;

    MPI_Reduce(&cnt, &final_cnt, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
        printf("The total number of occurances of %d is %d\n", target, final_cnt);

    MPI_Finalize();
    return 0;
}