#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "header.h"

int main(void) {
	FILE* input = fopen("in.txt", "rb");

	if (input == NULL) {
		return 1;
	}

	FILE* output = fopen("out.txt", "wb");

	if (output == NULL) {
		fclose(input);
		return 1;
	}

	int mode = fgetc(input);

	if (mode == EOF) {
		fclose(input);
		fclose(output);
		return 1;
	}

	if (mode == 'c') {
		encode(input, output);
	}
	else if (mode == 'd') {
		decode(input, output);
	}
	else {
		fclose(input);
		fclose(output);
		return 1;
	}

	fclose(input);
	fclose(output);

	return 0;
}
