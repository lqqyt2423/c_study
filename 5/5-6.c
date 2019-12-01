#include <stdio.h>
#include <string.h>
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

void reverse(char *s) {
	int c, i, j;
	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

void itoa(int n, char *s) {
	char *rs = s;
	int sign = n;
	if (sign < 0)
		n = -n;
	do {
		*s++ = n % 10 + '0';
	} while ((n /= 10) > 0);
	if (sign < 0)
		*s++ = '-';
	*s = '\0';
	reverse(rs);
}

int main() {
	char s[MAXSIZE];
	printf("line len: %d\n", _getline(s, MAXSIZE));
	printf("line: %s", s);

	printf("%d\n", atoi("123"));

	reverse(s);
	printf("%s\n", s);

	itoa(-345, s);
	printf("%s\n", s);
}
