
#include <mpi.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
int average(float* arr, int m)
{
	float sum=0;
	for(int i=0; i<m;i++)
	{
		sum+=arr[i];
	}
	return sum/m;
}
int main(int argc, char *argv[])
{
	int rank,size,n,m,i;
	float arr[100],avg,c[10],tot=0,b[10];
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank==0)
	{
		n=size;
		fprintf(stdout,"Enter m: \n");
		fflush(stdout);
		scanf("%d",&m);
		for(int i=0; i<(m*n);i++)
		{
			scanf("%f",&arr[i]);
		}
	}

	MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(arr,m,MPI_FLOAT,c, m, MPI_FLOAT,0,MPI_COMM_WORLD);
	avg=average(c,m);
	fprintf(stdout,"my avg: %f in process %d \n",avg,rank);
	fflush(stdout);
	MPI_Gather(&avg,1, MPI_FLOAT,b, 1,MPI_FLOAT, 0, MPI_COMM_WORLD);
	if(rank==0)
	{
		fprintf(stdout,"Result gathered in root \n");
		fflush(stdout);
		tot=average(b,n);
		fprintf(stdout,"%f \n",tot);
		fflush(stdout);
	}
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
	return 0;
}
