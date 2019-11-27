#include <stdio.h>

#define swap(t, x, y) { t _z; _z = y; y = x; x = _z; }

int main() {
  char s[] = "ab";
  swap(char, s[0], s[1]);
  printf("%s\n", s);
}