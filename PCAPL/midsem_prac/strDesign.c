#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, len, charspp;
    char str1[100], str2[100], ch[100], str[100];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter String-1: \n");
        scanf("%s", str1);
        printf("Enter String-2: \n");
        scanf("%s", str2);
    }

    MPI_Scatter(str1, 1, MPI_CHAR, &ch[0], 1, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(str2, 1, MPI_CHAR, &ch[1], 1, MPI_CHAR, 0, MPI_COMM_WORLD);
    ch[2] = '\0';

    MPI_Gather(ch, 2, MPI_CHAR, str, 2, MPI_CHAR, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        str[strlen(str1) * 2] = '\0';
        printf("The modified string is: %s\n", str);
    }

    MPI_Finalize();
    return 0;
}