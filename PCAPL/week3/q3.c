#include <stdio.h>
#include <string.h> 
#include <mpi.h>

int non_vowel_count(char arr[100], int length){
    int cnt = 0;
    for(int i = 0; i < length; i++)
        if(arr[i] == 'a' || arr[i] == 'e' || arr[i] == 'o' || arr[i] == 'i' || arr[i] == 'u')
            continue;
        else
            cnt++;
    return cnt; 
}

int main(int argc, char *argv[]){

    int size, rank, length, cnt, m, B[100]; 
    char str[100] = {0};
    char A[100] = {0};
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        printf("Enter string: ");
        scanf("%s", str);
        m = strlen(str) / size; 
    }
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(str, m, MPI_CHAR, A, m, MPI_CHAR, 0, MPI_COMM_WORLD);

    cnt = non_vowel_count(A, m);

    MPI_Gather(&cnt, 1, MPI_INT, B, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0){
        int total = 0;
        printf("Non-vowels found by each process: ");
        for(int i = 0; i < size; i++){
            total += B[i];
            printf("%d ", B[i]);
        }
        printf("\nTotal non-vowels: %d\n", total);      
    }
    MPI_Finalize();
    return 0; 
}