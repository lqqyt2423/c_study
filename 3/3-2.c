#include <stdio.h>

#define CHAR_LEN 100

void escape(char s[], char t[]) {
	int i, j;
	for (i = j = 0; s[i] != '\0'; i++) {
		switch (s[i]) {
			case '\n':
				t[j++] = '\\';
				t[j++] = 'n';
				break;
			case '\t':
				t[j++] = '\\';
				t[j++] = 't';
				break;
			default:
				t[j++] = s[i];
		}
	}
	t[j] = '\0';
}

void unescape(char s[], char t[]) {
	int i, j;
	for (i = j = 0; s[i] != '\0'; i++) {
		if (s[i] != '\\') {
			t[j++] = s[i];
			continue;
		}

		switch (s[++i]) {
			case 'n':
				t[j++] = '\n';
				break;
			case 't':
				t[j++] = '\t';
				break;
			default:
				t[j++] = '\\';
				t[j++] = s[i];
		}
	}
	t[j] = '\0';
}

int main() {
	char s[] = "hello	world\nhi";
	char t[CHAR_LEN];
	char j[CHAR_LEN];
	escape(s, t);
	unescape(t, j);
	printf("%s\n", s);
	printf("%s\n", t);
	printf("%s\n", j);
	return 0;
}
