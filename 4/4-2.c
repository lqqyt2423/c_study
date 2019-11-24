#include <stdio.h>
#include <ctype.h>

double atof(char s[]) {
	double val, power, edval;
	int i, sign, eval, esign;

	for (i = 0; isspace(s[i]); i++)
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}

	if (s[i] == 'e' || s[i] == 'E') {
		i++;
		esign = (s[i] == '-') ? -1 : 1;
		if (s[i] == '+' || s[i] == '-')
			i++;
		for (eval = 0; isdigit(s[i]); i++)
			eval = 10 * eval + (s[i] - '0');
		edval = 1;
		while (eval-- > 0)
			edval = 10 * edval;
		if (esign == -1) edval = 1 / edval;
		return sign * val / power * edval;
	} else {
		return sign * val / power;
	}
}

int main() {
	printf("123.45: %.2f\n", atof("123.45"));
	printf("0.233: %.3f\n", atof("0.233"));
	printf("123.45e6: %.2f\n", atof("123.45e6"));
	printf("123.45e-6: %.10f\n", atof("123.45e-6"));
	printf("123.45E6: %.2f\n", atof("123.45E6"));
	printf("123.45E-6: %.10f\n", atof("123.45E-6"));
}
