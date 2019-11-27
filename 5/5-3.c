#include <stdio.h>
#define MAXSIZE 100

void _strcat(char *s, char *t) {
	while (*s != '\0')
		s++;
	while (*t != '\0')
		*s++ = *t++;
	*s = '\0';
}

int main() {
	char s[MAXSIZE] = "hello";
	char t[MAXSIZE] = " world";
	_strcat(s, t);
	printf("%s\n", s);
}
