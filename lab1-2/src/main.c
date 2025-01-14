#include <stdio.h>
#include <string.h>
#include "header.h"

int main(void) {
	char substr[32],
		str[512];

	if (fgets(substr, 32, stdin) == NULL) 
		return 0;

	size_t i = 0,
		offset = 0,
		id_part = 0,
		shift[32] = { 0 },
		substr_len = strlen(substr) - 1,
		str_len;

	if (substr_len == 0)
		return 0;

	create_shift(substr, substr_len, shift);

	while (i < substr_len) {
		printf("%zu ", shift[i]);
		i++;
	}

	printf("\n");

	while ((str_len = fread(str + offset, sizeof(char), 256 - offset, stdin) + offset) >= substr_len) {
		offset = search_KMP(str, substr, str_len, substr_len, shift, id_part);
		id_part += str_len - offset;
		memmove(str, str + str_len - offset, offset);
	}

	return 0;
}
