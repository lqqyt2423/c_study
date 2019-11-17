#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

// 华氏度至摄氏度转换
int main() {
	int f;
	for (f = LOWER; f <= UPPER; f += STEP)
		printf("%3d %6.1f\n", f, (5.0/9.0)*(f-32));
}
