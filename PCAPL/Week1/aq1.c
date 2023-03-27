#include<stdio.h>
#include<mpi.h>

int revDigit(int n)
{
	int rev=0;
  	while (n!=0) 
  	{
    	rev=rev*10 + n%10;
    	n /= 10;
  	}

  	return rev;
}

int main(int argc, char *argv[])
{
	int rank,size;
	int arr[] ={18,523,301,1234,2,14,108,150,1928}; 
	MPI_Init(&argc,&argv);

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	printf("Process with rank %d gives rev value of %d\n",rank,revDigit(arr[rank]));
	MPI_Finalize();

	printf("\n");
	return 0;
}