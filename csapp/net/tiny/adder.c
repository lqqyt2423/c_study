#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

int main() {
  char *buf, *p;
  char arg1[MAXLINE], arg2[MAXLINE], content[MAXLINE];
  int n1 = 0, n2 = 0;

  // extract the two arguments
  if ((buf = getenv("QUERY_STRING")) != NULL) {
    p = strchr(buf, '&');
    *p = '\0';
    strcpy(arg1, buf);
    strcpy(arg2, p+1);
    n1 = atoi(arg1);
    n2 = atoi(arg2);
  }

  // make the response body
  sprintf(content, "QUERY_STRING=%s", buf);
  sprintf(content, "<p>welcome to add.com: ");
  sprintf(content, "%sthe internet addition portal.\r\n</p>", content);
  sprintf(content, "%s<p>the answer is: %d + %d = %d\r\n</p>", content, n1, n2, n1 + n2);
  sprintf(content, "%s<p>thanks for visiting!\r\n</p>", content);

  // generate the http response
  printf("Connection: close\r\n");
  printf("Content-length: %d\r\n", (int)strlen(content));
  printf("Content-type: text/html\r\n\r\n");
  printf("%s", content);
  fflush(stdout);
}
