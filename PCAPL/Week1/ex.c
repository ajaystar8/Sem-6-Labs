#include<stdio.h>
#include<mpi.h>

int main(int argc, char *argv[])
{
	int rank,size;
	MPI_Init(&argc,&argv);

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	printf("Process %d from total %d processes\n",rank,size);
	MPI_Finalize();

	return 0;
}

/*
Student@dslab-pc:~/200905170/Week1$ mpicc -o ex ex.c
Student@dslab-pc:~/200905170/Week1$ mpirun -n 4 ./ex
Process 0 from total 4 processes
Process 2 from total 4 processes
Process 3 from total 4 processes
Process 1 from total 4 processes
*/