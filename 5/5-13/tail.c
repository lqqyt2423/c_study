#include "tail.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int n = 10;

  if (argc == 3 && (strcmp(argv[1], "-n") == 0)) {
    n = atoi(argv[2]);
    if (n <= 0) n = 10;
  }

  char **lines = (char **)(malloc(n * sizeof(char *)));
  char line[MAXLINE];
  int begin = 0;
  int lineCount = 0;
  int lineLen;

  while ((lineLen = _getline(line, MAXLINE)) > 0) {
    char *currentLine = (char *)(malloc(lineLen * sizeof(char)));
    strcpy(currentLine, line);

    if (++lineCount > n) {
      free((void *)lines[begin]);
    }

    lines[begin] = currentLine;
    begin = (begin + 1) % n;
  }

  if (lineCount <= n) {
    for (int i = 0; i < lineCount; i++) {
      printf("%s", lines[i]);
    }
  } else {
    for (int i = begin, c = 0; c < n; i = (i + 1) % n, c++) {
      printf("%s", lines[i]);
    }
  }
}
