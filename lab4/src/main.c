#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main(void) {
	char exp[1024] = { '\0' };
	struct node* top = NULL;

	//push(&top, -1, '!');

	if (fgets(exp, 1024, stdin) == NULL) {
		return 0;
	}
	
	check(exp);
	parse(exp, &top);
	printf("%d", counting(&top));

	return 0;
}
