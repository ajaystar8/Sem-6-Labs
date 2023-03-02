#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]){
    int rank, size, fact = 1, factsum, N = 1;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    N = rank + 1;

    MPI_Scan(&N, &fact, 1, MPI_INT, MPI_PROD, MPI_COMM_WORLD);

    MPI_Reduce(&fact, &factsum, 1, MPI_INT, MPI_SUM,0,  MPI_COMM_WORLD);

    if(rank == 0)
        printf("Sum of all the factorials till process-%d= %d\n", rank, factsum);

    MPI_Finalize();
    return 0; 
}