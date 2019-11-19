#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
  size_t i;
  for (i = 0; i < len; i++) printf(" %.2x", start[i]);
  printf("\n");
}

void show_int(int x) { show_bytes((byte_pointer)&x, sizeof(int)); }

void show_float(float x) { show_bytes((byte_pointer)&x, sizeof(float)); }

void show_pointer(void *x) { show_bytes((byte_pointer)&x, sizeof(void *)); }

void show_char(char x) { show_bytes((byte_pointer)&x, sizeof(char)); }

int main() {
  char x = ~((unsigned char)~0 >> 1);
  show_char(x);
  return 0;
}
