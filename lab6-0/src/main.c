#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main(void){
	size_t i = 0,
			n;
	int val;

	struct node* root = NULL;

	if (scanf("%zu", &n) == 0) {
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
		i++;
	}

	printf("%d", height(root));
	free(Nodes);

	return 0;
}
