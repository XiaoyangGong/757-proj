/*
 * critical-fs tests false sharing on critical path
 *
 * Author: Xiaoyang Gong
 */
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <iostream>
#include <random>
#include <ctime>

int main(int argc, const char** argv) {
    srand(time(0));
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

    double  sum = 0.0; 
    double* sum_local = new double[nthreads];

    for(int i = 0; i < nthreads; i++){
        sum_local[i] = ((double)rand()) / ((double)RAND_MAX);
    }
    printf("sum_local initialized\n");

    printf("Start false sharing test...\n");
    #pragma omp parallel num_threads(nthreads)
    {
    int me = omp_get_thread_num();
    
    #pragma omp for schedule(static, 1)
    for (int i = 0; i < size; i++){
        sum_local[me] = sum_local[me] + me + i;
        #pragma omp atomic
        sum += sum_local[me];
    }
    }
    
    printf("Finish false sharing test\n");
    exit(1);
}


