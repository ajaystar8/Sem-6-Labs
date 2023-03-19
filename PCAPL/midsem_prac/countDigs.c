#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>
#include <ctype.h>

int countDigits(char substr[100], int len_str)
{
    int digs = 0;
    for (int i = 0; i < len_str; i++)
        if (isdigit(substr[i]))
            digs++;
    return digs;
}

int main(int argc, char *argv[])
{
    int size, rank, len_str;
    char *str;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        str = (char *)malloc(100 * sizeof(char));
        str = "aja2app8aja1app9";
        len_str = strlen(str) / size;
    }

    MPI_Bcast(&len_str, 1, MPI_INT, 0, MPI_COMM_WORLD);

    char substr[100];
    int sum, digs;
    substr[len_str] = '\0';

    MPI_Scatter(str, len_str, MPI_CHAR, substr, len_str, MPI_CHAR, 0, MPI_COMM_WORLD);

    digs = countDigits(substr, len_str);

    MPI_Reduce(&digs, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
        printf("The total number of digits in given string: %d\n", sum);

    MPI_Finalize();
    return 0;
}