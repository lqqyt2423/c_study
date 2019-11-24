#include <stdio.h>
#include <string.h>

int strrindex(char s[], char t[]) {
	int sl = strlen(s);
	int tl = strlen(t);

	int i, j, k;
	for (i = sl-1; i >= tl-1; i--) {
		for (j = i, k = tl-1; k >= 0 && s[j] == t[k]; k--, j--)
			;
		if (k < 0) return j + 1;
	}
	return -1;
}

int main() {
	char s[] = "hello world";
	char t[] = "wora";
	int i = strrindex(s, t);
	printf("right index: %d\n", i);
}
