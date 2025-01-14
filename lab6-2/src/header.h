#pragma once

struct Tree {
	int* nodes;
	int height;
	int degree;
	int root;
	int count;
	int maxCount;
};

void createTree(struct Tree* tree, int degree, int maxCount);
void insertT(struct Tree* tree, int val);
int createNode(struct Tree* tree, int** node);
void insertN(struct Tree* tree, int* node, int height, int val);
int index(int* keys, int count, int val);
