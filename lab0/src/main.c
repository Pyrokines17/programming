#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "header.h"
#define size 16

int main(void) {
	unsigned int base1,
		base2;

	if (scanf("%ud", &base1) != 1) {
		printf("bad input");
		return 0;
	}
	if (scanf("%ud", &base2) != 1) {
		printf("bad input");
		return 0;
	}
	if (base1 < 2 || base1 > 16 || base2 < 2 || base2 > 16) {
		printf("bad input");
		return 0;
	}

	char trash = getchar(), 
		string[size];

	if (fgets(string, size, stdin) == NULL && trash != 0) {
		printf("bad input");
		return 0;
	}

	double x;
	int err;
	char out[64] = { 0 };

	x = StrToNumber(string, base1, &err);

	if (err == 1) {
		printf("bad input");
		return 0;
	}

	printf("%s", NumberToStr(out, x, base2));

	return 0;
}
