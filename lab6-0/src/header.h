#pragma once

struct node {
	int key;
	unsigned char height;
	struct node* left;
	struct node* right;
};

struct node* create_node(int val, struct node* mem);
struct node* insert(struct node* Node, int val, struct node* mem);
struct node* balance(struct node* Node);
struct node* rotate_right(struct node* Node);
struct node* rotate_left(struct node* Node);
void fix_height(struct node* Node);
char height(struct node* Node);
int compare(struct node* Node);
