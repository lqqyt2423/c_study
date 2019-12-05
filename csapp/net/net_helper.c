#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define LISTENQ 1024

int open_clientfd(char *hostname, char *port) {
  int clientfd;
  struct addrinfo hints, *listp, *p;

  // get a list of potential server addresses
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_socktype = SOCK_STREAM; // open a connection
  hints.ai_flags = AI_NUMERICSERV; // using a numeric port arg.
  hints.ai_flags |= AI_ADDRCONFIG; // recomended for connections
  getaddrinfo(hostname, port, &hints, &listp);

  // walk the list for one that we can successfully connect to
  for (p = listp; p; p = p->ai_next) {
    // create a socket descriptor
    if ((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) {
      continue; // socket failed, try the next
    }

    // connect to the server
    if (connect(clientfd, p->ai_addr, p->ai_addrlen) != -1) {
      break; // success
    }
    close(clientfd); // connect failed, try another
  }

  freeaddrinfo(listp); // clean up
  if (!p) { // all connects failed
    return -1;
  } else { // the last connect succeeded
    return clientfd;
  }
}


int open_listenfd(char *port) {
  struct addrinfo hints, *listp, *p;
  int listenfd, optval = 1;

  // get a list of potential servr addresses
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_socktype = SOCK_STREAM; // accept connections
  hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG; // on any ip address
  hints.ai_flags |= AI_NUMERICSERV; // using port number
  getaddrinfo(NULL, port, &hints, &listp);

  // walk the list for one that we can bind to
  for (p = listp; p; p = p->ai_next) {
    // create a socket descriptor
    if ((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) {
      continue; // socket failed, try the next
    }

    // eliminates "address already in use" error from bind
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int));

    // bind the descriptor to the address
    if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0) {
      break; // success
    }
    close(listenfd); // bind failed, try the next
  }

  freeaddrinfo(listp); // clean up
  if (!p) { // no address worked
    return -1;
  }

  // make it a listening socket ready to accept connection requests
  if (listen(listenfd, LISTENQ) < 0) {
    close(listenfd);
    return -1;
  }

  return listenfd;
}
