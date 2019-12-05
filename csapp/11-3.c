#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXBUF 1000

int main(int argc, char **argv) {
  struct in_addr inaddr;
  int rc;

  if (argc != 2) {
    fprintf(stderr, "usage: %s <dotted-decimal>\n", argv[0]);
    exit(0);
  }

  rc = inet_pton(AF_INET, argv[1], &inaddr);
  if (rc <= 0) {
    fprintf(stderr, "error\n");
    exit(0);
  }

  printf("0x%x\n", ntohl(inaddr.s_addr));
}
