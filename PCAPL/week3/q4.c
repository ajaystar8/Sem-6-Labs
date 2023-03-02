#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char *argv[]){
    int rank, size, l;
    char s1[100], s2[100], s[100],ch[100];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        printf("Enter first string: ");
        scanf("%s", s1);
        printf("Enter second string: ");
        scanf("%s", s2);
        l = strlen(s1);
    }
    MPI_Bcast(&l, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(s1, 1, MPI_CHAR, &ch[0], 1, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(s2, 1, MPI_CHAR, &ch[1], 1, MPI_CHAR, 0, MPI_COMM_WORLD);
    ch[2] = '\0';

    MPI_Gather(ch, 2, MPI_CHAR, s, 2, MPI_CHAR, 0, MPI_COMM_WORLD);

    if(rank == 0){
        s[l*2] = '\0';
        printf("Combined string: %s\n", s);
    }
    MPI_Finalize();
    return 0;   
}