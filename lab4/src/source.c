#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "header.h"

void check(const char* exp) {
	size_t i = 0;
	char bracket = 0,
		number = 0,
		point = 0,
		empty = 0,
		op = 0;

	while (exp[i] != '\n' && exp[i] != '\0') {
		if (exp[i] == '(') {
			bracket++;

			if (exp[i + 1] == ')') {
				empty++;
			}
		}

		if (exp[i] == ')') {
			bracket--;
		}

		if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/') {
			op++;
		}

		if (isdigit(exp[i])) {
			while (isdigit(exp[i])) {
				i++;
			}

			number++;
			i--;
		}

		if (exp[i] == '.') {
			point++;
		}

		i++;
	}

	if (i == 0 || bracket != 0 || (op == 0 && (number > 1)) || number == 0 || point != 0 || op >= number || empty != 0) {
		printf("syntax error");

		exit(0);
	}
}

void parse(const char* exp, struct node** top) {
	size_t i = 0,
		i1 = 0,
		len = strlen(exp) - 1;
	int x = 0;
	char digits[16] = { '\0' };
	struct node* top1 = NULL;

	//push(top1, -1, '!');

	while (i < len) {
		while (exp[i] != '\0' && exp[i] != '\n' && isspace(exp[i])) {
			i++;
		}

		if (exp[i] == '\0' || exp[i] == '\n') {
			break;
		}

		switch (exp[i]) {
		case '(':
			push(top, -1, '(');

			break;
		case ')':
			while (*top != NULL && peek(top, 1) != '(') {
				push(&top1, -1, peek(top, 1));
				pop(top);
			}

			if (*top == NULL) {
				printf("syntax error");

				exit(0);
			}

			pop(top);

			break;
		case '*':
			while (*top != NULL && (peek(top, 1) == '/' || peek(top, 1) == '*')) {
				push(&top1, -1, peek(top, 1));
				pop(top);
			}
			push(top, -1, '*');

			break;
		case '/':
			while (*top != NULL && (peek(top, 1) == '/' || peek(top, 1) == '*')) {
				push(&top1, -1, peek(top, 1));
				pop(top);
			}
			push(top, -1, '/');

			break;
		case '+':
			while (*top != NULL && peek(top, 1) != '(') {
				push(&top1, -1, peek(top, 1));
				pop(top);
			}
			push(top, -1, '+');

			break;
		case '-':
			while (*top != NULL && peek(top, 1) != '(') {
				push(&top1, -1, peek(top, 1));
				pop(top);
			}
			push(top, -1, '-');

			break;
		default:
			i1 = 0;

			while (isdigit(exp[i])) {
				digits[i1] = exp[i];
				i1++;
				i++;
			};

			x = StrToNum(digits);
			push(&top1, x, -1);
			i--;

			break;
		}

		i++;
	}

	while (*top != NULL) {
		push(&top1, -1, peek(top, 1));
		pop(top);
	}

	while (top1 != NULL) {
		push(top, peek(&top1, 0), peek(&top1, 1));
		pop(&top1);
	}
}

int counting(struct node** top) {
	int res = 0;
	struct node* top1 = NULL;

	while (*top != NULL) {

		if (peek(top, 1) == '+' || peek(top, 1) == '-' || peek(top, 1) == '*' || peek(top, 1) == '/') {
			int x = peek(&top1, 0);
			pop(&top1);
			int y = peek(&top1, 0);
			pop(&top1);

			switch (peek(top, 1)) {
			case '+':
				push(&top1, y + x, -1);
				pop(top);

				break;
			case '-':
				push(&top1, y - x, -1);
				pop(top);

				break;
			case '*': 
				push(&top1, y * x, -1);
				pop(top);

				break;
			case '/': 
				if (x == 0) {
					printf("division by zero");

					exit(0);
				}

				push(&top1, y / x, -1);
				pop(top);

				break;
			}
		}
		else {
			push(&top1, peek(top, 0), -1);
			pop(top);
		}
	}

	res = peek(&top1, 0);

	free(top1);

	return res;
}

int StrToNum(char* str) {
	int i = 0,
		x = 0;
	
	while (i < 16 && str[i] != '\0') {
		int d = str[i] - '0';
		
		x = x * 10 + d;
		str[i] = '\0';
		i++;
	}

	return x;
}
