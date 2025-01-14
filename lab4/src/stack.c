#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void push(struct node** top, int number, char op) {
	struct node* Node = (struct node*)malloc(sizeof(struct node));

	if (Node == NULL) {
		printf("Error");

		exit(0);
	}
	
	Node->number = number;
	Node->op = op;
	Node->next = *top;
	*top = Node;
}

int peek(struct node** top, char choice) {
	if (top == NULL) {
		printf("Error");

		exit(0);
	}

	if (choice == 0) {
		return (*top)->number;
	}
	else {
		return (*top)->op;
	}
}

void pop(struct node** top) {
	struct node* Node;

	if (top == NULL) {
		printf("Error");

		exit(0);
	}

	Node = *top;
	*top = (*top)->next;
	free(Node);
}
