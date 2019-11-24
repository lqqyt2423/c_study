#include <stdio.h>

// 将字符串s2中的任一字符在字符串s1中的第一次出现的位置作为结果返回

int any(char s1[], char s2[]) {
	int i, j;
	for (i = 0; s1[i] != '\0'; i++) {
		for (j = 0; s2[j] != '\0'; j++)
			if (s2[j] == s1[i])
				return i;
	}
	return -1;
}

int main() {
	int index = any("hello world", "iqiangd");
	printf("index: %d\n", index);
	return 0;
}
