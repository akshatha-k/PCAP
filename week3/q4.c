
#include <mpi.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	int rank,size,i,len,m,b[10],count,sum=0;
	char s1[30],s2[30],c1[30],c2[30],final[30];
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank==0)
	{
		printf("Enter a string: \n");
		scanf("%s",s1);
		printf("Enter a string: \n");
		scanf("%s",s2);
		if((strlen(s1)%size)!=0 || (strlen(s2)%size)!=0)
			exit(0);
	}
	m=strlen(s1)/size;
	MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(s1,m,MPI_CHAR,c1, m, MPI_CHAR,0,MPI_COMM_WORLD);
	MPI_Scatter(s2,m,MPI_CHAR,c2, m, MPI_CHAR,0,MPI_COMM_WORLD);
	strcat(c1,c2);
	//fprintf(stdout,"my str: %s in process %d \n",c1,rank);
	//fflush(stdout);
	MPI_Gather(&c1,m*2, MPI_CHAR,final, m*2,MPI_CHAR, 0, MPI_COMM_WORLD);
	if(rank==0)
	{
		printf("FINAL: %s \n",final);
	}
	MPI_Finalize();
	return 0;
}
