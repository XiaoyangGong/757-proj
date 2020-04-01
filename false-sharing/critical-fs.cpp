#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, const char** argv) {
    if (argc != 3) {
      printf("Usage: ./critical-fs <nthreads> <size>\n");
      exit(1);
    }
   
    int nthreads = atoi(argv[1]);
   
    if (nthreads < 1) {
      printf("nthreads must be 1 or more\n");
      exit(1);
    }
    
    int size = atoi(argv[2]);
 
    if (size < 1) {
      printf("size must be 1 or more\n");
      exit(1);
    }
   
    printf("Setting OMP threads to %d\n", nthreads);

    double sum=0.0, sum_local[nthreads], x[size], y[size];
    for(int i = 0; i < size; i++){
        x[i] = i;
        y[i] = i*i - i;
    }
    printf("x,y initialized\n");

    printf("Start false sharing test...\n");
    #pragma omp parallel num_threads(nthreads)
    {
    int me = omp_get_thread_num();
    sum_local[me] = 0.0;
    
    #pragma omp for
    for (int i = 0; i < size; i++)
        sum_local[me] += x[i] * y[i];
    
    #pragma omp atomic
    sum += sum_local[me];
    }
}
