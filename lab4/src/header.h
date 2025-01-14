#pragma once

struct node {
	int number;
	char op;
	struct node* next;
};

void push(struct node** top, int number, char op);
int peek(struct node** top, char choice);
void pop(struct node** top);

void check(const char* exp);
void parse(const char* exp, struct node** top);
int counting(struct node** top);
int StrToNum(char* str);
