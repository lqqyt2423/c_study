#include <pthread.h>
#include <stdio.h>

void *thread(void *vargp);

int main() {
  pthread_t tid;
  pthread_create(&tid, NULL, thread, NULL);
  pthread_join(tid, NULL);
}

void *thread(void *vargp) {
  printf("hello world\n");
  return NULL;
}
