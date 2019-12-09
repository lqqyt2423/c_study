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
void command(void);

int main(int argc, char **argv) {
  int listenfd, connfd;
  socklen_t clientlen;
  struct sockaddr_storage clientaddr;
  fd_set read_set, ready_set;

  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(0);
  }
  listenfd = open_listenfd(argv[1]);

  FD_ZERO(&read_set);               // clear read set
  FD_SET(STDIN_FILENO, &read_set);  // add stdin to read set
  FD_SET(listenfd, &read_set);      // add listenfd to read set

  while (1) {
    ready_set = read_set;
    select(listenfd + 1, &ready_set, NULL, NULL, NULL);
    if (FD_ISSET(STDIN_FILENO, &ready_set)) {
      command();  // read command line from stdin
    }
    if (FD_ISSET(listenfd, &ready_set)) {
      clientlen = sizeof(struct sockaddr_storage);
      connfd = accept(listenfd, (SA *)&clientaddr, &clientlen);
      echo(connfd);
      close(connfd);
    }
  }
}

void command(void) {
  char buf[MAXLINE];
  if (!fgets(buf, MAXLINE, stdin)) {
    exit(0);
  }
  printf("%s", buf);
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
