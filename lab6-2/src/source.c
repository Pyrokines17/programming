#include <stdlib.h>
#include <string.h>
#include "header.h"

void createTree(struct Tree* tree, int degree, int maxCountK) {
	int maxCountN = maxCountK / (degree - 1) + 1;

	tree->nodes = (int*)malloc((size_t)(16 * degree * maxCountN));

	if (tree->nodes == NULL) {
		exit(1);
	}

	tree->height = 0;
	tree->degree = degree;
	tree->root = 0;
	tree->count = 1;
	tree->maxCount = maxCountN;
	*tree->nodes = 0;
}

void insertT(struct Tree* tree, int val) {
	if (tree->height == 0) {
		tree->height = 1;
	}

	int root = tree->root;
	int* node0 = tree->nodes + 4 * tree->degree * root;

	if (*node0 == 2 * tree->degree - 1) {
		int* node1;
		int* newNode0;

		tree->root = createNode(tree, &newNode0);
		*newNode0 = 1;
		
		(newNode0 + 2 * tree->degree)[0] = root;
		(newNode0 + 2 * tree->degree)[1] = createNode(tree, &node1);

		memcpy(node1 + 1, node0 + 1 + tree->degree, sizeof(int) * (size_t)(tree->degree - 1));
		memcpy(node1 + 2 * tree->degree, node0 + 2 * tree->degree + tree->degree, sizeof(int) * tree->degree);
		
		*node0 = tree->degree - 1;
		*node1 = tree->degree - 1;
		
		(newNode0 + 1)[0] = (node0 + 1)[tree->degree - 1];
		tree->height++;
		node0 = newNode0;
	}

	insertN(tree, node0, tree->height - 1, val);
}

int createNode(struct Tree* tree, int** node) {
	*node = tree->nodes + 4 * tree->degree * tree->count;
	**node = 0;

	return tree->count++;
}

void insertN(struct Tree* tree, int* node, int height, int val) {
	int count = *node;

	if (height > 0) {
		int id = index(node, count, val);
		int* childs = node + 2 * tree->degree;
		int* child = tree->nodes + 4 * tree->degree * childs[id];

		if (*child == 2 * tree->degree - 1) {
			int* keys = node + 1;

			for (int i = count; i > id; i--) {
				childs[i + 1] = childs[i];
				keys[i] = keys[i - 1];
			}

			int* childAlt;

			childs[id + 1] = createNode(tree, &childAlt);

			memcpy(childAlt + 1, child + 1 + tree->degree, sizeof(int) * tree->degree);
			memcpy(childAlt + 2 * tree->degree, child + 2 * tree->degree + tree->degree, sizeof(int) * tree->degree);

			*child = tree->degree - 1;
			*childAlt = tree->degree - 1;

			keys[id] = (child + 1)[tree->degree - 1];
			(*node)++;
			id = index(node, count + 1, val);
			child = tree->nodes + 4 * tree->degree * childs[id];
		}

		insertN(tree, child, height - 1, val);
	}
	else {
		int* keys = node + 1;
		int i = count;

		while (i > 0) {
			int key = keys[i - 1];

			if (key <= val) {
				break;
			}

			keys[i--] = key;
		}

		keys[i] = val;
		(*node)++;
	}
}

int index(int* keys, int count, int val) {
	if (count == 0) {
		return 0;
	}

	int id = 0,
		n = count;

	while (n - id > 1) {
		int x = (n + id) / 2,
			y = keys[x];

		if (y == val) {
			break;
		}

		if (y < val) {
			id = x;
		}
		else {
			n = x;
		}
	}

	if (keys[id] < val) {
		return id + 1;
	}

	return id;
}
