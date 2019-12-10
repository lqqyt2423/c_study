#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXTHREADS 32

void *sum_mutex(void *vargp);

long gsum = 0;
long nelems_per_thread;
sem_t mutex;

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
  sem_init(&mutex, 0, 1);

  for (i = 0; i < nthreads; i++) {
    myid[i] = i;
    pthread_create(&tid[i], NULL, sum_mutex, &myid[i]);
  }

  for (i = 0; i < nthreads; i++) {
    pthread_join(tid[i], NULL);
  }

  if (gsum != (nelems * (nelems - 1)) / 2) {
    printf("error: result=%ld\n", gsum);
  }

  time(&end_time);
  time_cost = difftime(end_time, begin_time);
  printf("cost: %.1f\n", time_cost);

  exit(0);
}

void *sum_mutex(void *vargp) {
  long myid = *((long *)vargp);
  long start = myid * nelems_per_thread;
  long end = start + nelems_per_thread;
  long i;

  for (i = start; i < end; i++) {
    sem_wait(&mutex);
    gsum += i;
    sem_post(&mutex);
  }

  return NULL;
}
