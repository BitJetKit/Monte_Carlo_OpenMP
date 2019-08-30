// File: Monte_carlo_OpenMP
// Purpose: Parallelize Monte_carlo method utilizing OpenMP library
// Author: Jonathan M. Kelly
// Date: 13 December 2016

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[])
{
  int number_in_circle;
  int i = 0;
  long long int thread_count;
  unsigned int randSeed[4];
  double x, y;
  double distance_squared;
  double pi_estimate;

  thread_count = strtol(argv[1], NULL, 10);

#pragma omp parallel
{
  randSeed[0] = 1;
  randSeed[1] = 1;
  randSeed[2] = 1;
  randSeed[3] = omp_get_thread_num();
  number_in_circle = 0;
  printf("Hello from thread %d\n", randSeed[3]);
  srandom(randSeed[3]);
#pragma omp for firstprivate(randSeed) private(x,y) reduction(+: number_in_circle)
    for (i = 0; i < thread_count; i++)
      {
	x = 2*random()/((double)RAND_MAX) - 1.0;
	y = 2*random()/((double)RAND_MAX) - 1.0;
	distance_squared = x*x + y*y;
	if (distance_squared <= 1.0)
	  {
	    number_in_circle++;
	  }
      }  
 }
      pi_estimate = 4.0* (double) number_in_circle / (double) thread_count;
      printf("Number in Circle = %d\n Thread count = %lld\n Pi estimate: %f\n", number_in_circle, thread_count, pi_estimate);
      return 0;
} /* Monte_carlo */

