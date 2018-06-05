#include <omp.h>
#include <stdio.h>
#define NUM_THREADS 2
static long num_steps = 100000;
double step;

void main () {
	int i, nthreads; 
	double pi;
	step = 1.0/(double) num_steps;
	omp_set_num_threads(NUM_THREADS);
	#pragma omp parallel
	{
		int i, id, nthreds;
		double x, sum;
		id = omp_get_thread_num();
		nthreds = omp_get_num_threads();
		if (id==0) nthreads = nthreds;
		
		for (i=id, sum=0.0;i< num_steps; i=i+nthreds){
			x = (i+0.5)*step;
			sum = sum + 4.0/(1.0+x*x);
		}
		#pragma omp critical
		pi += step * sum;
	}
	printf("%f\n",pi);
}

//#pragma omp parallel
//#pragma omp critical
