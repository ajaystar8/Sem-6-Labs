// WAP in MPI to toggle the characters of a given string indexed by the rank of the process. 
//Hint: i/p - HeLLO , 5 processes, p0 toggles H - h, p1 toggles e - E and so on

#include<stdio.h>
#include<mpi.h>
#include<ctype.h>

char toggle(char in)
{
	if(isupper(in))
		in+=32;
	else
		in-=32;

	return in;
}


int main(int argc, char *argv[])
{
	int rank,size;
	char str[]="HeLLO";
	MPI_Init(&argc,&argv);

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	printf("Process with rank %d toggles character %c to %c\n",rank,str[rank],toggle(str[rank]));

	MPI_Finalize();
	return 0;
}
