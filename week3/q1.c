
#include <mpi.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
int factorial(int num)
{
	int i=1,fact=1;
	while(i<=num)
	{
		fact=fact*i;
		i++;
	}
	return fact;
}
int main(int argc, char *argv[])
{
	int rank,size,N,A[10],B[10],c,i,sum=0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank==0)
	{
		N=size;
		printf("Enter %d values: \n",N);
		for(int i=0; i<N;i++)
		{
			scanf("%d",&A[i]);
		}
	}
		MPI_Scatter(A,1,MPI_INT,&c, 1, MPI_INT,0,MPI_COMM_WORLD);
		//fprintf(stdout,"I have received %d in process %d: \n",c,rank);
		//fflush(stdout);
	c=factorial(c);
	MPI_Gather(&c,1, MPI_INT,B, 1,MPI_INT, 0, MPI_COMM_WORLD);
	if(rank==0)
	{
		printf("Result gathered in root \n");
		for(int i=0; i<N;i++)
		{
			sum+=B[i];
		}
		printf("%d \n",sum);
	}
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
	return 0;
}
