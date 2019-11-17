#include <stdio.h>

int main() {
	long i;

	for (i = 0; getchar() != EOF; ++i)
		;

	printf("char count: %ld\n", i);
}
