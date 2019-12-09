#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../rio/rio.h"
#include "net_helper.h"

typedef struct sockaddr SA;

#define MAXLINE 1000

void echo(int connfd);

typedef struct {
  int maxfd;
  fd_set read_set;
  fd_set ready_set;
  int nready;
  int maxi;
  int clientfd[FD_SETSIZE];
  rio_t clientrio[FD_SETSIZE];
} pool;

void init_pool(int, pool *);
void add_client(int, pool *);
void check_clients(pool *);

int byte_cnt = 0;

int main(int argc, char **argv) {
  int listenfd, connfd;
  socklen_t clientlen;
  struct sockaddr_storage clientaddr;
  static pool pool;

  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(0);
  }
  listenfd = open_listenfd(argv[1]);
  printf("listenfd: %d\n", listenfd);
  init_pool(listenfd, &pool);
  printf("init_pool\n");

  while (1) {
    pool.ready_set = pool.read_set;
    pool.nready = select(pool.maxfd + 1, &pool.ready_set, NULL, NULL, NULL);
    printf("pool.nready: %d\n", pool.nready);

    if (FD_ISSET(listenfd, &pool.ready_set)) {
      clientlen = sizeof(struct sockaddr_storage);
      connfd = accept(listenfd, (SA *)&clientaddr, &clientlen);
      printf("confd: %d\n", connfd);
      add_client(connfd, &pool);
    }

    check_clients(&pool);
  }
}

void init_pool(int listenfd, pool *p) {
  int i;
  p->maxi = -1;
  for (i = 0; i < FD_SETSIZE; i++) p->clientfd[i] = -1;
  p->maxfd = listenfd;
  FD_ZERO(&p->read_set);
  FD_SET(listenfd, &p->read_set);
}

void add_client(int connfd, pool *p) {
  int i;
  p->nready--;
  for (i = 0; i < FD_SETSIZE; i++) {
    if (p->clientfd[i] < 0) {
      p->clientfd[i] = connfd;
      rio_readinitb(&p->clientrio[i], connfd);

      FD_SET(connfd, &p->read_set);

      if (connfd > p->maxfd) p->maxfd = connfd;
      if (i > p->maxi) p->maxi = i;
      break;
    }
  }

  if (i == FD_SETSIZE) {
    fprintf(stderr, "add_client error: too many clients\n");
    exit(1);
  }
}

void check_clients(pool *p) {
  int i, connfd, n;
  char buf[MAXLINE];
  rio_t rio;

  for (i = 0; (i <= p->maxi) && (p->nready > 0); i++) {
    connfd = p->clientfd[i];
    rio = p->clientrio[i];

    if ((connfd > 0) && (FD_ISSET(connfd, &p->ready_set))) {
      p->nready--;
      if ((n = rio_readlineb(&rio, buf, MAXLINE)) != 0) {
        byte_cnt += n;
        printf("server received %d (%d total) bytes on fd %d\n", n, byte_cnt,
               connfd);
        rio_writen(connfd, buf, n);
      }

      else {
        close(connfd);
        FD_CLR(connfd, &p->read_set);
        p->clientfd[i] = -1;
      }
    }
  }
}
