#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, rep;
    char str[100], res[100], c, final_res[100];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter string: \n");
        scanf("%s", str);
    }
    MPI_Scatter(str, 1, MPI_CHAR, &c, 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    rep = rank + 1;
    for (int i = 0; i < rep; i++)
        res[i] = c;
    res[rank + 1] = '\0';
    printf("%s\n", res);

    MPI_Gather(res, strlen(res) + 1, MPI_CHAR, final_res, strlen(res) + 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    if (rank == 0)
        printf("The final string is: %s\n", final_res);

    MPI_Finalize();
    return 0;
}