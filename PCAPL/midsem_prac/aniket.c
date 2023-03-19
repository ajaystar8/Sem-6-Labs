#include <stdio.h>
#include <mpi.h>
#include <string.h>

int substrMatch(char word[], char substr[], int len, int slen)
{
    int i, j;
    for (i = 0; i < len - slen + 1; i++)
    {
        for (j = 0; j < slen; j++)
            if (word[i + j] != substr[j])
                break;
        if (j == slen)
            return 1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int len, slen;
    if (!rank)
    {
        printf("Enter length of words : \n");
        scanf("%d", &len);
    }
    MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);

    char words[size][len + 1], substr[100], word[len + 1];
    if (!rank)
    {
        printf("Enter the words : \n");
        for (int i = 0; i < size; i++)
            scanf("%s", words[i]);
        printf("Enter the substring : \n");
        scanf("%s", substr);
        slen = strlen(substr);
    }
    MPI_Bcast(&slen, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(substr, slen + 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    MPI_Scatter(words, len + 1, MPI_CHAR, word, len + 1, MPI_CHAR, 0, MPI_COMM_WORLD);
    printf("%s\n", word);
    int found = substrMatch(word, substr, len, slen);

    int match[size];
    if (rank)
        MPI_Send(&found, 1, MPI_INT, 0, rank, MPI_COMM_WORLD);
    else
    {
        match[0] = found;
        for (int i = 1; i < size; i++)
            MPI_Recv(&match[i], 1, MPI_INT, i, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (int i = 0; i < size; i++)
            printf("%d : %s\n", i, match[i] ? "Found" : "Not found");
    }

    MPI_Finalize();
    return 0;
}