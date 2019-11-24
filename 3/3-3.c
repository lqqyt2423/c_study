#include <stdio.h>
#define CHAR_LEN 1000

void expand(char s1[], char s2[]) {
	int i = 0;
	int j = 0;
	while (s1[i] != '\0') {
		if (i == 0) {
			s2[j++] = s1[i++];
			continue;
		}
		if (s1[i] != '-') {
			s2[j++] = s1[i++];
			continue;
		}
		if (s1[i+1] > s1[i-1]) {
			while ((s2[j] = s2[j-1] + 1) < s1[i+1])
				++j;
			++i;
			++i;
			++j;
		} else {
			s2[j++] = s1[i++];
		}
	}
	s2[j] = '\0';
}

void expand2(char s1[], char s2[]) {
	char c;
	int i, j;
	i = j = 0;
	while ((c = s1[i++]) != '\0') {
		if (s1[i] == '-' && s1[i+1] >= c) {
			i++;
			while (c < s1[i])
				s2[j++] = c++;
		} else {
			s2[j++] = c;
		}
	}
	s2[j] = '\0';
}

int main() {
	char s1[] = "a-zA-Z0-99-0a-f";
	char s2[CHAR_LEN];
	expand2(s1, s2);
	printf("%s\n", s2);
}
