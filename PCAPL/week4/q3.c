#include <stdio.h>
#include "mpi.h"

void ErrorHandler(int err_code){
    if(err_code != MPI_SUCCESS){
        char error_string[BUFSIZ];
        int length_err_string, err_class;
        MPI_Error_class(err_code, &err_class);
        MPI_Error_string(err_code, error_string, &length_err_string);
        fprintf(stderr, "Error: %d %s\n", err_class, error_string);
    }
}

int main(int argc, char *argv[]){
    int rank, size, err_code, arr[3][3], n, result;
    MPI_Init(&argc, &argv);
    MPI_Errhandler_set(MPI_COMM_WORLD,MPI_ERRORS_RETURN);
    err_code = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    err_code = MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        printf("Enter 9 elements: ");
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                scanf("%d", &arr[i][j]);
        
        printf("Element to be searched: ");
        scanf("%d", &n);
    }
    int sarr[3], res = 0;
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(arr, 3, MPI_INT, sarr, 3, MPI_INT, 0, MPI_COMM_WORLD);
    for(int i = 0; i < 3; i++)
        if(sarr[i] == n)
            res++;
    err_code = MPI_Reduce(&res, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if(rank == 0){
        ErrorHandler(err_code);
        printf("Total number of occurences is: %d\n", result);
    }


    MPI_Finalize();
    return 0; 
}