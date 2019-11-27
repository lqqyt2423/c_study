#include <stdio.h>
#define MAXSIZE 100

int _getline(char *s, int lim) {
	int c;
	char *t = s;
	while (lim-- > 0 && (c = getchar()) != EOF && c != '\n')
		*s++ = c;
	if (c == '\n')
		*s++ = c;
	*s++ = '\0';
	return s - t;
}

int atoi(char *s) {
	int n = 0;
	while (*s >= '0' && *s <= '9') {
		n = 10 * n + (*s - '0');
		s++;
	}
	return n;
}

// int itoa(int n, char *s) {
// }

int main() {
	char s[MAXSIZE];
	printf("line len: %d\n", _getline(s, MAXSIZE));
	printf("line: %s", s);

	printf("%d\n", atoi("123"));
}
