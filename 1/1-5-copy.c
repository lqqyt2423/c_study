#include <stdio.h>

int main() {
	// 后面要放 EOF，所以定义为 int
	int c;

	while ((c = getchar()) != EOF)
		putchar(c);
}
