#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	int size, rank;
	int i,j,c=0;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if (rank==0)
	{
		for(i=1;i<50;i++)
		{
			c=0;
			for(j=1;j<=i;j++)
			{
				if (i%j==0)
					c++;
			}
			if (c==2)
				printf("Process %d, %d\n",rank,i);
		}
	}	
	else
	{
		for(i=50;i<=100;i++)
		{
			c=0;
			for(j=1;j<=i;j++)
			{
				if (i%j==0)
					c++;
			}
			if (c==2)
				printf("Process %d, %d\n",rank,i);
		}
	}

	MPI_Finalize();

	return 0;
}