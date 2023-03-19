#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    char str[100], c, subarr[100], res[100];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter the string: \n");
        scanf("%s", str);
    }
    MPI_Scatter(str, 1, MPI_CHAR, &c, 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    int i = 0;
    for (i = 0; i < rank + 1; i++)
        subarr[i] = c;
    subarr[i] = '\0';

    MPI_Gather(subarr, i + 1, MPI_CHAR, res, i + 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    if (rank == 0)
        printf("The resultant string is: %s\n", res);

    MPI_Finalize();
    return 0;
}