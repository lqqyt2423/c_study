#include <unistd.h>
#define RIO_BUFSIZE 8192

typedef struct {
  int rio_fd;                 // descriptor for this internal buf
  int rio_cnt;                // unread bytes in internal buf
  char *rio_bufptr;           // next unread byte in internal buf
  char rio_buf[RIO_BUFSIZE];  // internal buffer
} rio_t;

// 无缓冲
ssize_t rio_readn(int fd, void *usrbuf, size_t n);
ssize_t rio_writen(int fd, void *usrbuf, size_t n);

// 带缓冲
void rio_readinitb(rio_t *rp, int fd);
ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);
ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n);
