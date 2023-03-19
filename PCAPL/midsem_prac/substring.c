#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int substrMatch(char str[100], int len, char substr[100], int slen)
{
    int found = 1;
    for (int i = 0; i < len - slen + 1; i++)
    {
        for (int j = 0; j < slen; j++)
        {
            if (str[i + j] != substr[j])
            {
                found = 0;
                break;
            }
        }
        if (found)
            return 1;
        found = 1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int rank, size, len, slen, result[100], found;
    char substr[100], subarr[100];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter length of strings: \n");
        scanf("%d", &len);
    }

    MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);
    char arr[size][len + 1];

    if (rank == 0)
    {
        printf("Enter %d strings: \n", size);
        for (int i = 0; i < size; i++)
            scanf("%s", arr[i]);
        printf("Enter length of substring: \n");
        scanf("%d", &slen);
        printf("Enter substring: \n");
        scanf("%s", substr);
    }
    MPI_Bcast(&slen, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(substr, slen + 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    MPI_Scatter(arr[rank], len + 1, MPI_CHAR, subarr, len + 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    found = substrMatch(subarr, len, substr, slen);

    MPI_Gather(&found, 1, MPI_INT, result, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
        for (int i = 0; i < size; i++)
            printf("Process-%d: %s\n", i, result[i] ? "found" : "not found");

    MPI_Finalize();
    return 0;
}