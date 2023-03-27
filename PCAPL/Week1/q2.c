//WAP in MPI where even ranked process prints "Hello" and odd ranked process prints "World"

#include<stdio.h>
#include<mpi.h>

int main(int argc, char *argv[])
{
	int rank,size;
	MPI_Init(&argc,&argv);

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank%2==0)
		printf("Process with rank %d, Hello\n",rank);
	else
		printf("Process with rank %d, World\n",rank);
	MPI_Finalize();

	return 0;
}
