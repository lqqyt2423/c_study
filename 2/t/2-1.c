#include <limits.h>
#include <stdio.h>

// 打印各种类型的取值范围

void printFromLib() {
  printf("signed char: %d ~ %d\n", SCHAR_MIN, SCHAR_MAX);
  printf("unsigned char: 0 ~ %u\n", UCHAR_MAX);
  printf("signed short: %d ~ %d\n", SHRT_MIN, SHRT_MAX);
  printf("unsigned short: 0 ~ %u\n", USHRT_MAX);
  printf("signed int: %d ~ %d\n", INT_MIN, INT_MAX);
  printf("unsigned int: 0 ~ %u\n", UINT_MAX);
  printf("signed long: %ld ~ %ld\n", LONG_MIN, LONG_MAX);
  printf("unsigned long: 0 ~ %lu\n", ULONG_MAX);
}

void printByCalc() {
  char min_c = ~((unsigned char)~0 >> 1);
  printf("signed char min: %d\n", min_c);
  char max_c = (unsigned char)~0 >> 1;
  printf("signed char max: %d\n", max_c);

  short min_s = ~((unsigned short)~0 >> 1);
  printf("signed short min: %d\n", min_s);
  short max_s = (unsigned short)~0 >> 1;
  printf("signed short max: %d\n", max_s);

  int min_i = ~((unsigned int)~0 >> 1);
  printf("signed int min: %d\n", min_i);
  int max_i = (unsigned int)~0 >> 1;
  printf("signed int max: %d\n", max_i);

  long min_l = ~((unsigned long)~0 >> 1);
  printf("signed long min: %ld\n", min_l);
  long max_l = (unsigned long)~0 >> 1;
  printf("signed long max: %ld\n", max_l);

  unsigned char max_u_c = ~0;
  printf("unsigned char max: %u\n", max_u_c);

  unsigned short max_u_s = ~0;
  printf("unsigned short max: %u\n", max_u_s);

  unsigned int max_u_i = ~0;
  printf("unsigned int max: %u\n", max_u_i);

  unsigned long max_u_l = ~0;
  printf("unsigned long max: %lu\n", max_u_l);
}

int main() {
  printFromLib();
  printf("\n");
  printByCalc();
  return 0;
}
