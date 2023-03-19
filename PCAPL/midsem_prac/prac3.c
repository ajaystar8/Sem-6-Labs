#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, len;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter the length of strings: \n");
        scanf("%d", &len);
    }
    MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);
    char arr[size][len + 1], subarr[len + 1];
    if (rank == 0)
    {
        printf("Enter the strings: \n");
        for (int i = 0; i < size; i++)
            scanf("%s", arr[i]);
        for (int i = 0; i < size; i++)
            MPI_Send(arr[i], len + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Recv(subarr, len + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("String recieved is %s\n", subarr);
    }

    MPI_Finalize();
    return 0;
}