#include <stdio.h>

int strend(char *s, char *t) {
	int sl, tl;
	char *rs = s;
	char *rt = t;
	for (sl = 0; *s != '\0'; s++)
		sl++;
	for (tl = 0; *t != '\0'; t++)
		tl++;
	if (sl < tl) return 0;

	for (t = rt, s = rs + sl - tl; *s == *t; t++, s++)
		;
	return (t - rt) < tl ? 0 : 1;
}

int main() {
	printf("strend('abc', 'bc'): %d\n", strend("abc", "bc"));
	printf("strend('abc', 'bd'): %d\n", strend("abc", "bd"));
	printf("%d\n", strend("hello world", "rld"));
	printf("%d\n", strend("hello world", "worl"));
}
