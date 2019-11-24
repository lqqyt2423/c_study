#include <stdio.h>

// 返回x中从第p位开始的n位
unsigned getbits(unsigned x, int p, int n) {
	return (x >> (p+1-n)) & ~(~0 << n);
}

// 将x中从p为开始的n个位设置为y中最右边n位的值
unsigned setbits(unsigned x, int p, int n, unsigned y) {
	unsigned tx, ty;
	tx = x & ~(~(~0 << n) << (p+1-n));
	ty = (y & ~(~0 << n)) << (p+1-n);
	return tx | ty;
}

// 将x中从第p位开始的n个位求反
unsigned revert(unsigned x, int p, int n) {
	return x ^ (~(~0 << n) << (p+1-n));
}
