#include <stdio.h>
#include <stdlib.h>
#include "header.h"

struct node* create_node(int val, struct node* mem) {
	struct node* Node = mem;

	Node->left = NULL;
	Node->right = NULL;
	Node->key = val;
	Node->color = 1;

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
	if (!is_red(Node->right) && is_red(Node->left) && is_red(Node->left->right)) {
		Node->left = rotate_left(Node->left);
	}
	else if (!is_red(Node->left) && is_red(Node->right) && is_red(Node->right->left)) {
		Node->right = rotate_right(Node->right);
	}

	if (!is_red(Node->right) && is_red(Node->left) && is_red(Node->left->left)) {
		Node = rotate_right(Node);
	}
	else if (!is_red(Node->left) && is_red(Node->right) && is_red(Node->right->right)) {
		Node = rotate_left(Node);
	}

	if (is_red(Node->left) && is_red(Node->right) && (is_red(Node->left->left) || is_red(Node->left->right) || is_red(Node->right->left) || is_red(Node->right->right))) {
		flip_colors(Node);
	}

	return Node;
}

struct node* rotate_right(struct node* Node) {
	struct node* Node1 = Node->left;
	
	Node1->color = Node->color;
	Node->color = 1;
	Node->left = Node1->right;
	Node1->right = Node;

	return Node1;
}

struct node* rotate_left(struct node* Node) {
	struct node* Node1 = Node->right;
	
	Node1->color = Node->color;
	Node->color = 1;
	Node->right = Node1->left;
	Node1->left = Node;

	return Node1;
}

void flip_colors(struct node* Node) {
	Node->color = !Node->color;
	Node->left->color = !Node->left->color;
	Node->right->color = !Node->right->color;
}

char is_red(struct node* Node) {
	return (Node ? Node->color : 0);
}

int height(struct node* Node) {
	if (Node == NULL) {
		return 1;
	}

	if (Node->color == 0) {
		return height(Node->left) + 1;
	}
	else {
		return height(Node->left);
	}
}
