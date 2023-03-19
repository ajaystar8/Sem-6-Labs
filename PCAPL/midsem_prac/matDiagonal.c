#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, arr1[4][4], arr2[4][4], subarr[4], subarr2[4], max = -1, min = 1000, max_elems[4], min_elems[4], sum[4];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter 16 elements for 4x4 matrix-1: \n");
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                scanf("%d", &arr1[i][j]);
        printf("Enter 16 elements for 4x4 matrix-2: \n");
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                scanf("%d", &arr2[i][j]);
    }

    // arr1 - max of column
    // arr2 - min of row

    // SENDING COLUMNS OF arr1
    for (int i = 0; i < size; i++)
        MPI_Scatter(arr1[i], 1, MPI_INT, subarr, 1, MPI_INT, 0, MPI_COMM_WORLD);
    for (int i = 0; i < 4; i++)
        if (subarr[i] > max)
            max = subarr[i];
    MPI_Gather(&max, 1, MPI_INT, max_elems, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // SENDING ROWS OF arr2
    MPI_Scatter(arr2[rank], 4, MPI_INT, subarr2, 4, MPI_INT, 0, MPI_COMM_WORLD);
    for (int i = 0; i < 4; i++)
        if (subarr2[i] < min)
            min = subarr2[i];
    MPI_Gather(&min, 1, MPI_INT, min_elems, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        for (int i = 0; i < 4; i++)
            sum[i] = max_elems[i] + min_elems[i];

        // replacing the minimum elements by the sum element
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (arr2[i][j] == min_elems[i])
                    arr2[i][j] = sum[i];

        // making the unchanged primary diagonal element to zero
        for (int i = 0; i < 4; i++)
            if (arr2[i][i] != sum[i])
                arr2[i][i] = 0;

        // printing the updated arr2
        printf("Updated arr2: \n");
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
                printf("%d ", arr2[i][j]);
            printf("\n");
        }
    }
    MPI_Finalize();
    return 0;
}