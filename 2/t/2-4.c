#include <stdio.h>

// 将字符串s1中任何与字符串s2中字符匹配的字符都删除

void squeeze1(char s1[], char s2[]) {
	int i, j;
	for (i = j = 0; s1[i] != '\0'; i++) {
		int isIn = 0;
		for (int k = 0; s2[k] != '\0'; k++) {
			if (s2[k] == s1[i]) {
				isIn = 1;
				break;
			}
		}
		if (!isIn) s1[j++] = s1[i];
	}
	s1[j] = '\0';
}

// 答案
void squeeze2(char s1[], char s2[]) {
	int i, j, k;
	for (i = j = 0; s1[i] != '\0'; i++) {
		for (k = 0; s2[k] != '\0' && s2[k] != s1[i]; k++)
			;
		if (s2[k] == '\0')
			s1[j++] = s1[i];
	}
	s1[j] = '\0';
}

int main() {
	char s1[] = "abcdefgabcdefg";
	char s2[] = "bd";
	squeeze2(s1, s2);
	printf("s1: %s\n", s1);
 }
