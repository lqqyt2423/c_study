#include <stdio.h>

// 把由十六进制数字组成的字符串转换为与之等价的整型值

int htoi(char s[]) {
	int i = 0;
	int n = 0;

	if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) i = 2;

	while (1) {
		int cn;

		if (s[i] >= '0' && s[i] <= '9') {
			cn = s[i] - '0';
		} else if (s[i] >= 'A' && s[i] <= 'F') {
			cn = s[i] - 'A' + 10;
		} else if (s[i] >= 'a' && s[i] <= 'f') {
			cn = s[i] - 'a' + 10;
		} else {
			return n;
		}
		n = n * 16 + cn;
		i++;
	}
}

int main() {
	printf("10: %d\n", htoi("10"));
	printf("0x20: %d\n", htoi("0x20"));
	printf("0X35: %d\n", htoi("0X35"));
	printf("0X1f: %d\n", htoi("0X1f"));
	printf("0X5A: %d\n", htoi("0X5A"));
	printf("abc: %d\n", htoi("abc"));
	printf("zzz: %d\n", htoi("zzz"));
	return 0;
}
