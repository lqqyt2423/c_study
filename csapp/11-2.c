#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define MAXBUF 1000

int main(int argc, char **argv) {
  struct in_addr inaddr;
  uint32_t addr;
  char buf[MAXBUF];

  if (argc != 2) {
    fprintf(stderr, "usage: %s <hex number>\n", argv[0]);
    exit(0);
  }
  sscanf(argv[1], "%x", &addr);
  inaddr.s_addr = htonl(addr);

  if (!inet_ntop(AF_INET, &inaddr, buf, MAXBUF)) {
    printf("error\n");
    exit(1);
  }
  printf("%s\n", buf);
}
