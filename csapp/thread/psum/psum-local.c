#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXTHREADS 32

void *sum_array(void *vargp);

long gsum = 0;
long nelems_per_thread;
long psum[MAXTHREADS];

int main(int argc, char **argv) {
  time_t begin_time, end_time;
  double time_cost;
  time(&begin_time);

  long i, nelems, log_nelems, nthreads, myid[MAXTHREADS];
  pthread_t tid[MAXTHREADS];

  if (argc != 3) {
    printf("usage: %s <nthreads> <log_nelems>\n", argv[0]);
    exit(0);
  }

  nthreads = atoi(argv[1]);
  log_nelems = atoi(argv[2]);
  nelems = (1L << log_nelems);
  nelems_per_thread = nelems / nthreads;

  for (i = 0; i < nthreads; i++) {
    myid[i] = i;
    pthread_create(&tid[i], NULL, sum_array, &myid[i]);
  }

  for (i = 0; i < nthreads; i++) {
    pthread_join(tid[i], NULL);
  }

  for (i = 0; i < nthreads; i++) {
    gsum += psum[i];
  }

  if (gsum != (nelems * (nelems - 1)) / 2) {
    printf("error: result=%ld\n", gsum);
  }

  time(&end_time);
  time_cost = difftime(end_time, begin_time);
  printf("cost: %.1f\n", time_cost);

  exit(0);
}

void *sum_array(void *vargp) {
  long myid = *((long *)vargp);
  long start = myid * nelems_per_thread;
  long end = start + nelems_per_thread;
  long i, sum = 0;

  for (i = start; i < end; i++) {
    sum += i;
  }
  psum[myid] = sum;

  return NULL;
}
