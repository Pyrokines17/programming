#pragma once

struct node {
	int key;
	char color;
	struct node* left;
	struct node* right;
};

struct node* create_node(int val, struct node* mem);
struct node* insert(struct node* Node, int val, struct node* mem);
struct node* balance(struct node* Node);
struct node* rotate_right(struct node* Node);
struct node* rotate_left(struct node* Node);
void flip_colors(struct node* Node);
char is_red(struct node* Node);
int height(struct node* Node);
