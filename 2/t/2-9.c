#include <stdio.h>

int bitcount(unsigned x) {
	int b;
	for (b = 0; x != 0; x &= (x-1))
		++b;
	return b;
}

int main() {
	for (unsigned i = 1; i < 100; i++)
		printf("%u: %d\n", i, bitcount(i));
}
