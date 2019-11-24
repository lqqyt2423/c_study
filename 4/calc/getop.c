#include <stdio.h>
#include <ctype.h>
#include "calc.h"

int getop(char s[]) {
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.' && c != '-')
		return c;
	// 识别负数
	if (c == '-') {
		if (isdigit(c = getch())) {
			s[0] = '-';
			s[1] = c;
			i = 1;
		} else {
			if (c != EOF)
				ungetch(c);
			return '-';
		}
	} else {
		i = 0;
	}

	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}
