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
		substr_len = strlen(substr) - 1,
		shift[256],
		offset = 0,
		id_part = 0;

	create_shift(shift, substr, substr_len);

	while ((str_len = fread(str + offset, sizeof(char), 256 - offset, stdin)) > 0) {
		offset = BMH_search(str, str_len, substr, substr_len, shift, id_part);
		id_part += str_len - offset;
		memmove(str, str + str_len - offset, offset);
	}

	return 0;
}
