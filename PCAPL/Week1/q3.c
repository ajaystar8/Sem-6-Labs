//WAP in MPI to simulate simple calculator. Perform each operation using diffrent processes in parallel

#include<stdio.h>
#include<mpi.h>

int main(int argc, char *argv[])
{
	int rank,size;
	int x=4,y=3;
	int res;
	MPI_Init(&argc,&argv);

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	switch(rank)
	{
		case 0: res = x+y;
				printf("Process with rank %d gives sum %d\n",rank,res);
		break;
		case 1: res = x-y;
				printf("Process with rank %d gives diffrence %d\n",rank,res);
		break;
		case 2: res = x*y;
				printf("Process with rank %d gives product %d\n",rank,res);
		break;
		case 3: res = x/y;
				printf("Process with rank %d gives quotient %d\n",rank,res);
		break;
		case 4: res = x%y;
				printf("Process with rank %d gives modulo %d\n",rank,res);
		break;
	}

	MPI_Finalize();
	return 0;
}
