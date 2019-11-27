#include <stdio.h>
#define MAXSIZE 100

char *_strncpy(char *s, char *ct, int n) {
	char *rs = s;
	while (*ct && n > 0) {
		*s++ = *ct++;
		n--;
	}
	*s = '\0';
	while (n > 0) {
		*s++ = '\0';
		n--;
	}
	return rs;
}

char *_strncat(char *s, char *ct, int n) {
	char *rs = s;
	while (*s)
		s++;
	while (*ct && n > 0) {
		*s++ = *ct++;
		n--;
	}
	*s = '\0';
	while (n > 0) {
		*s++ = '\0';
		n--;
	}
	return rs;
}

int _strncmp(char *cs, char *ct, int n) {
	while (*cs && *cs == *ct && n > 0) {
		cs++;
		ct++;
		n--;
	}
	if (*cs == '\0' || *ct == '\0') return 0;
	return *cs - *ct;
}

int main() {
	char a[MAXSIZE] = "hello";
	char b[MAXSIZE] = "hi how are you i am fine";
	_strncpy(a, b, 6);
	printf("%s\n", a);
	_strncat(a, b, 6);
	printf("%s\n", a);
	printf("%d\n", _strncmp("abcaagdagad", "abcaaaa", 3));
	printf("%d\n", _strncmp("abcaagdagad", "abcaaaa", 6));
	printf("%d\n", _strncmp("abcaaaa", "abcaagdagad", 6));
}
