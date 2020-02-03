//COPYRIGHT @KOLMOGROV
#include <stdio.h>
#include <mpi.h>
#include "err.h"
#define low (-100)
#define high 100
#define h 1  
double func(double x)
{
	return 4/(1+x*x);
}
int main(int argc, char *argv[])
{
	int rank, size,errc;
	double sum=0, inter,area;
	errc=MPI_Init(&argc,&argv);
	MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);
	handle(errc);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	inter=(INT_MAX)/size;
	double i=low+rank*inter;
	while(i<(low+(rank+1)*inter))
	{
		sum+=func(i)*h;
		i=i+h;
	}
	MPI_Reduce(&sum,&area,1,MPI_DOUBLE, MPI_SUM,0,MPI_COMM_WORLD);
	if(rank==0)
	{
		printf("Area is= %g\n",area);
		printf("pi is= %g\n",area/4);
	}
	MPI_Finalize();
	return 0;
}