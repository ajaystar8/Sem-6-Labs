#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int countDigits(char word[], int len)
{
    int count = 0;
    for (int i = 0; i < len; i++)
        if (isdigit(word[i]))
            count++;
    return count;
}

int main(int argc, char *argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char *word, wordpp[100];
    int lenpp;
    if (!rank)
    {
        word = (char *)malloc(100 * sizeof(char));
        word = "aja2app8aja1app9";
        lenpp = strlen(word) / size;
    }

    MPI_Bcast(&lenpp, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(word, lenpp, MPI_CHAR, wordpp, lenpp, MPI_CHAR, 0, MPI_COMM_WORLD);
    wordpp[lenpp] = '\0';
    int count = countDigits(wordpp, lenpp), sum;
    MPI_Reduce(&count, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (!rank)
        printf("Total number of digits in entered string : %d\n", sum);

    MPI_Finalize();
    return 0;
}