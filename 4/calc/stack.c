#include <stdio.h>
#include "calc.h"
#define MAXVAL 100

static int sp = 0;
static double val[MAXVAL];

void push(double f) {
	if (sp < MAXVAL) {
		val[sp++] = f;
		// printf("push: %g\n", f);
	}
	else
		printf("error: stack full, can't push %g\n", f);
}

double pop(void) {
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

double peek() {
	if (sp > 0)
		return val[sp-1];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

void exchange() {
	if (sp < 2) {
		printf("less than 2\n");
		return;
	}

	double tmp = val[sp-1];
	val[sp-1] = val[sp-2];
	val[sp-2] = tmp;
}

void clear() {
	sp = 0;
}
