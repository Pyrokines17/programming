#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "Header.h"

int main(void) {
	unsigned int count, 
				end;
	char permutation[35], 
		RetValue;

	if (fgets(permutation, 35, stdin) == NULL) {
		printf("bad input");
		return 0;
	}

	end = (unsigned int)strlen(permutation) - 1;
	permutation[end] = '\0';
	RetValue = scanf("%ud", &count);

	if (check(permutation) == 1 && RetValue == 1) {
		printf("bad input");
		return 0;
	}
	else {
		unsigned int i = 0;
		
		while ((i < count) && next_permutation(permutation)) {
			printf("%s\n", permutation);
			i += 1;
		}
	}
	return 0;
}
