#include <math.h>
#include <stdlib.h>
#include <stdio.h>


double f(double x)
{
	exp(x)*sin(x);
}


double n_rand(double lambda)
{
	/* por ahora uso una distribucion exponencial para integrar */
	double u;
	u = rand() / (RAND_MAX + 1.0);

	return -log(1- u) / lambda;
}
;
double MCI(int N)
{
	double *x;
	x = malloc(sizeof(double *)*N);
	int i;
	for(i = 0; i < N; i++)
	{
            	x[i] = n_rand(0.05);
    	}

	double *F; 
	F = malloc(sizeof(double *)*N);

	for(i = 0; i < N; i++)
	{
            	F[i] = f(x[i]);
    	}

	double sum = 0.0;
	
	for(i = 0; i < N; i++)
	{
            	sum = sum + F[i];
    	}
	

	return sum/N; 
}

void main(int argc, char *argv[]) {


  /*Initialization */
 MPI_Init(&argc,&argv);
 MPI_Comm_size(MPI_COMM_WORLD,&size);
 MPI_Comm_rank(MPI_COMM_WORLD,&rank);
double integral;
 double valor;
 N=1000;
  if(rank!=0){
    valor=MCI(N/size);
    MPI_Reduce(&integral, &valor, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  }
  if(rank==0){
    printf("%lf", integral);
  }
  MPI_Finalize();

  return 0;
}
