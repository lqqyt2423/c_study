#include <stdio.h>

int main() {
	int i;
	while ((i = getchar()) != EOF) {
		if (i == '\t') {
			putchar('\\');
			putchar('t');
		} else if (i == '\\') {
			putchar('\\');
			putchar('\\');
		} else {
			putchar(i);
		}
	}
}
