#include <stdio.h>
#include <string.h>
#include "header.h"

int main(void) {
	char str[512], 
		substr[32];

	if (fgets(substr, 32, stdin) == NULL) {
		return 0;
	}

	size_t str_len,
		id_part = 0,
		offset = 0,
		substr_len = strlen(substr) - 1,
		substr_hash;
	int degree = 1;

	substr_hash = hash(substr, substr_len, &degree);
	printf("%zu ", substr_hash);

	while ((str_len = fread(str + offset, sizeof(char), 256 - offset, stdin) + offset) >= substr_len) {
		offset = RK_search(str, str_len, substr, substr_hash, substr_len, id_part);
		id_part += str_len - offset;
		memmove(str, str + str_len - offset, offset);
	}

	return 0;
}
