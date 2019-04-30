#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>
#include <omp.h>
#include "includeOpen.h"


double get_time() {

  struct timeval tv;

  gettimeofday(&tv, (void *)0);

  return (double) tv.tv_sec + tv.tv_usec*1e-6;

}


int main(int argc, char**argv)
{

  int n=0, size = atoi(argv[1]);
  int i,j,spin[size][size],runs;

  int ai,aj,T; // T est la température 

  int* tab = NULL;
  

  double start,stop;
  double cpu_time_used; 
  double en_old,en_new,H,r;
  double beta;

	runs = atoi(argv[2]);
  T = atoi(argv[3]);

//  int num_du_thread = 4;

  tab=malloc(pow(2,N*N)*sizeof(int));

  srand( time(NULL) );

  // initial fill
  for (i=0; i<N; i++)
  {
    for (j=0; j<N; j++)
    {
      spin[i][j] = updown();
      printf("%d", spin[i][j]);
    }
    printf("\n");
  }

  // K Valeur de BoltZmann wikipedia
  beta = 1/((1.38064852*pow(10,-23))*T);
  	 
  start = omp_get_wtime( );

  #pragma omp parallel for schedule(dynamic,100) 
    for(int run = 0; run<runs; run++)
    {
      monte_carlo(spin,tab,run,beta);
    }
  

  stop = omp_get_wtime( );  

  cpu_time_used = stop -start;
  
  

  ising_output(tab,cnt);

  printf("cnt = %d\n", cnt);

   printf("Time excution Mont Carlo %f\n", cpu_time_used);
   
   free(tab);

  return 0;
}
