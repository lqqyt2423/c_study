#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "../rio/rio.h"
#include "net_helper.h"
#include <sys/wait.h>
#include <sys/signal.h>

typedef struct sockaddr SA;

#define MAXLINE 1000

void echo(int connfd);

void sigchld_handler(int sig) {
  while (waitpid(-1, 0, WNOHANG) > 0)
    ;
  return;
}

int main(int argc, char **argv) {
  int listenfd, connfd;
  socklen_t clientlen;
  struct sockaddr_storage clientaddr;  // enough space for any address

  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(0);
  }

  signal(SIGCHLD, sigchld_handler);
  listenfd = open_listenfd(argv[1]);
  while (1) {
    clientlen = sizeof(struct sockaddr_storage);
    connfd = accept(listenfd, (SA *)&clientaddr, &clientlen);
    if (fork() == 0) {
      close(listenfd);
      echo(connfd);
      close(connfd);
      exit(0);
    }
    close(connfd); // parent closes connected socket (important!)
  }
}

void echo(int connfd) {
  size_t n;
  char buf[MAXLINE];
  rio_t rio;

  rio_readinitb(&rio, connfd);
  while ((n = rio_readlineb(&rio, buf, MAXLINE)) != 0) {
    printf("server received %d bytes\n", (int)n);
    rio_writen(connfd, buf, n);
  }
}
