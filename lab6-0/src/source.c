#include <stdio.h>
#include <stdlib.h>
#include "header.h"

struct node* create_node(int val, struct node* mem) {
	struct node* Node = mem;

	Node->left = NULL;
	Node->right = NULL;
	Node->key = val;
	Node->height = 1;

	return Node;
}

struct node* insert(struct node* Node, int val, struct node* mem) {
	if (Node == NULL) {
		return create_node(val, mem);
	}

	if (val < Node->key) {
		Node->left = insert(Node->left, val, mem);
	}
	else {
		Node->right = insert(Node->right, val, mem);
	}

	return balance(Node);
}

struct node* balance(struct node* Node) {
	fix_height(Node);

	if (compare(Node) == 2) {
		if (compare(Node->right) < 0) {
			Node->right = rotate_right(Node->right);
		}

		return rotate_left(Node);
	}

	if (compare(Node) == -2) {
		if (compare(Node->left) > 0) {
			Node->left = rotate_left(Node->left);
		}

		return rotate_right(Node);
	}

	return Node;
}

struct node* rotate_right(struct node* Node) {
	struct node* Node1 = Node->left;

	Node->left = Node1->right;
	Node1->right = Node;
	fix_height(Node);
	fix_height(Node1);

	return Node1;
}

struct node* rotate_left(struct node* Node) {
	struct node* Node1 = Node->right;

	Node->right = Node1->left;
	Node1->left = Node;
	fix_height(Node);
	fix_height(Node1);

	return Node1;
}

void fix_height(struct node* Node) {
	unsigned char hl = height(Node->left);
	unsigned char hr = height(Node->right);

	Node->height = (hl > hr ? hl : hr) + 1;
}

char height(struct node* Node) {
	return Node ? Node->height : 0;
}

int compare(struct node* Node) {
	return height(Node->right) - height(Node->left);
}
