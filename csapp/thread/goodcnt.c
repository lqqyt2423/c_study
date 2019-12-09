#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

void *thread(void *);
volatile long cnt = 0;
sem_t mutex;

int main(int argc, char **argv) {
  sem_init(&mutex, 0, 1);
  long niters;
  pthread_t tid1, tid2;

  if (argc != 2) {
    printf("usage: %s <niters>\n", argv[0]);
    exit(0);
  }
  niters = atoi(argv[1]);

  pthread_create(&tid1, NULL, thread, &niters);
  pthread_create(&tid2, NULL, thread, &niters);
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);

  if (cnt != (2 * niters)) {
    printf("boom! cnt=%ld\n", cnt);
  } else {
    printf("ok cnt=%ld\n", cnt);
  }
}

void *thread(void *vargp) {
  long i, niters = *((long *)vargp);
  for (i = 0; i < niters; i++) {
    sem_wait(&mutex);
    cnt++;
    sem_post(&mutex);
  }
  return NULL;
}
