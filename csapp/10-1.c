#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
  int fd1, fd2;

  fd1 = open("10-1.c", O_RDONLY, 0);
  printf("fd1 = %d\n", fd1);
  close(fd1);
  fd2 = open("mmapcopy.c", O_RDONLY, 0);
  printf("fd2 = %d\n",fd2);
  close(fd2);
}
