#include <stdio.h>

// x循环右移n位所得到的结果

int wordlength() {
	unsigned x;
	int i = 0;
	for (x = ~0; x > 0; x = x >> 1)
		i++;
	return i;
}

unsigned rightrot1(unsigned x, int n) {
	unsigned y;
	int len = wordlength();
	while (n-- > 0) {
		y = (x & 1) << (len - 1);
		x = x >> 1;
		x = x | y;
	}
	return x;
}

unsigned rightrot2(unsigned x, int n) {
	int len = wordlength();
	if ((n = n % len) > 0) {
		unsigned y = x << (len - n);
		x = x >> n;
		x = x | y;
	}
	return x;
}

int main() {
	printf("wordlength: %d\n", wordlength());
}
