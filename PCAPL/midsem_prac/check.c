#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int substringMatch(char str[100], int mainlen, char substr[100], int slen)
{
    int found = 1;
    for (int i = 0; i < mainlen - slen + 1; i++)
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
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int len;
    if (rank == 0)
    {
        printf("Enter length of strings: \n");
        scanf("%d", &len);
    }
    MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);

    char words[size][len + 1], word[len + 1], substr[len + 1];
    int slen;
    if (rank == 0)
    {
        printf("Enter %d strings: \n", size);
        for (int i = 0; i < size; i++)
            scanf("%s", words[i]);
        printf("Enter length of substring: \n");
        scanf("%d", &slen);
        printf("Enter the substring: \n");
        scanf("%s", substr);
    }
    MPI_Bcast(&slen, len + 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(substr, len + 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(words, len + 1, MPI_CHAR, word, len + 1, MPI_CHAR, 0, MPI_COMM_WORLD);
    word[len + 1] = '\0';

    int found = substringMatch(word, len, substr, slen);
    if (rank)
        MPI_Send(&found, 1, MPI_INT, 0, rank, MPI_COMM_WORLD);

    int result[size];
    if (rank == 0)
    {
        result[0] = found;
        for (int i = 1; i < size; i++)
            MPI_Recv(&result[i], 1, MPI_INT, i, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (int i = 0; i < size; i++)
            printf("%d : %s\n", i, result[i] ? "Found" : "Not found");
    }

    MPI_Finalize();
    return 0;
}