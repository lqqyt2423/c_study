#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int _getline(char *line, int max);

int main(int argc, char *argv[]) {
  char line[MAXLINE];
  int found = 0;

  if (argc != 2)
    printf("Usage: find pattern\n");
  else
    while (_getline(line, MAXLINE) > 0)
      if (strstr(line, argv[1]) != NULL) {
        printf("%s", line);
        found++;
      }

  printf("found: %d\n", found);
  return 0;
}

int _getline(char s[], int lim) {
  int c, i;

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) s[i] = c;
  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';
  return i;
}
