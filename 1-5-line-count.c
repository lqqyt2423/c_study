#include <stdio.h>

int main() {
	int i;
	long l = 0;

	while ((i = getchar()) != EOF)
		if (i == '\n')
			++l;

	printf("line count: %ld\n", l);
}
