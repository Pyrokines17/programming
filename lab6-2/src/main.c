#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main(void) {
	int t = 2,
		n = 0,
		i = 0,
		val = 0;
	struct Tree tree;

	if (scanf("%d %d", &t, &n) < 2) {
		return 1;
	}

	createTree(&tree, t, n);

	while (i < n) {
		if (scanf("%d", &val) != 1) {
			return 1;
		}

		insertT(&tree, val);

		i++;
	}

	printf("%d", tree.height);
	free((&tree)->nodes);

	return 0;
}
