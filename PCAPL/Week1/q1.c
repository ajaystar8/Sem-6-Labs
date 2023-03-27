//WAP in MPI to find out pow(x,rank) for all the processes where 'x' is the interger constant and 'rank' is the rank of the processes

#include<stdio.h>
#include<mpi.h>
#include<math.h>

int main(int argc, char *argv[])
{
	int rank,size;
	int x=2; 
	MPI_Init(&argc,&argv);

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	printf("Process with rank %d has value %f\n",rank,pow(x,rank));
	
	MPI_Finalize();
	return 0;
}
