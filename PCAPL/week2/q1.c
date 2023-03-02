#include "mpi.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int rank, size, word_length;
    char word[100]; 
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        // sending process
        printf("Enter a word: ");
        scanf("%s", word);
        word_length = strlen(word)+1;
        MPI_Ssend(&word_length, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Ssend(&word, word_length, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
        printf("Word sent.\n");
        MPI_Recv(&word, word_length, MPI_CHAR, 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Toggled word recieved is: %s\n", word);
    }
    else{
        MPI_Recv(&word_length, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&word, word_length, MPI_CHAR, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("The word recieved is: %s\n", word);
        for(int i = 0; i < word_length; i++){
            if(word[i] >= 'a' && word[i] <= 'z') 
                word[i] -= 32;
            else
                word[i] += 32;
        }
        printf("Word toggled and sent. \n");
        MPI_Ssend(&word, word_length, MPI_CHAR, 0, 2, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0; 
}