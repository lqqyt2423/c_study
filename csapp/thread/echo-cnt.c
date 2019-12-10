#include <pthread.h>
#include <semaphore.h>
#include "../rio/rio.h"

#define MAXLINE 1000

static int byte_cnt;
static sem_t mutex;

static void init_echo_cnt(void) {
  sem_init(&mutex, 0, 1);
  byte_cnt = 0;
}

void echo_cnt(int connfd) {
  int n;
  char buf[MAXLINE];
  rio_t rio;
  static pthread_once_t once = PTHREAD_ONCE_INIT;

  pthread_once(&once, init_echo_cnt);
  rio_readinitb(&rio, connfd);
  while ((n = rio_readlineb(&rio, buf, MAXLINE)) != 0) {
    sem_wait(&mutex);
    byte_cnt += n;
    printf("server received %d (%d total) bytes of fd %d\n", n, byte_cnt,
           connfd);
    sem_post(&mutex);
    rio_writen(connfd, buf, n);
  }
}
