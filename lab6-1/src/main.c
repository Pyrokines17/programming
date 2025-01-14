#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main(void) {
	size_t i = 0,
			n = 0;
	int val = 0;
	struct node* root = NULL;

	if (scanf("%zu", &n) == 0) {
		return 0;
	}

	if (n == 0) {
		printf("%d", 0);

		return 0;
	}

	struct node* Nodes = (struct node*)malloc(n * sizeof(struct node));

	if (Nodes == NULL) {
		return 0;
	}

	while (i < n) {
		if (scanf("%d", &val) == 0) {
			return 0;
		}

		root = insert(root, val, &Nodes[i]);
		root->color = 0;
		i++;
	}

	printf("%d", height(root));

	free(Nodes);

	return 0;
}
