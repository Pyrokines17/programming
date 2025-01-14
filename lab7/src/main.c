#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main(void) {
	int n = 0,
		m = 0;

	if (scanf("%d %d", &n, &m) < 2) {
		printf("bad number of lines");
		return 0;
	}

	if (!checkInput(n, m)) {
		return 0;
	}

	int sizeMatrix = (size_t)((n + 1) * (n + 1)) / (sizeof(unsigned int) * 8) + 1;
	unsigned int* matrix = (unsigned int*)malloc(sizeof(unsigned int) * sizeMatrix);

	if (matrix == NULL) {
		return 1;
	}

	char* color = (char*)malloc(sizeof(char) * (size_t)(n + 1));

	if (color == NULL) {
		free(matrix);
		return 1;
	}

	int* arrVertices = (int*)malloc(sizeof(int) * n);

	if (arrVertices == NULL) {
		free(matrix);
		free(color);
		return 1;
	}

	memset(matrix, 0, sizeof(unsigned int) * sizeMatrix);
	memset(color, 0, sizeof(char) * (size_t)(n + 1));

	for (int i = 0; i < m; i++) {
		int ver1,
			ver2;

		if (scanf("%d %d", &ver1, &ver2) < 2) {
			printf("bad number of lines");
			free(matrix);
			free(color);
			free(arrVertices);
			return 0;
		}

		if (!checkVertex(ver1, n) || !checkVertex(ver2, n)) {
			free(matrix);
			free(color);
			free(arrVertices);
			return 0;
		}

		int num = ver1 * n + ver2;

		matrix[num / (sizeof(unsigned int) * 8)] |= 1 << ((sizeof(unsigned int) * 8) - (num % (sizeof(unsigned int) * 8)));
	}

	if (!topSort(matrix, color, arrVertices, n)) {
		free(matrix);
		free(color);
		free(arrVertices);
		return 0;
	}

	for (int i = n - 1; i >= 0; i--) {
		printf("%d ", arrVertices[i]);
	}

	free(matrix);
	free(color);
	free(arrVertices);

	return 0;
}
