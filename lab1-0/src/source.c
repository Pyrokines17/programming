#include <stdio.h>
#include "header.h"

void create_shift(size_t shift[256], const char* substr, size_t substr_len) {
	size_t i = 0, 
		sym = 0;

	while (sym < 256) {
		shift[sym] = substr_len;
		sym += 1;
	}

	while (i < substr_len - 1) {
		sym = (size_t)substr[i] % 256;
		shift[sym] = substr_len - i - 1;
		i += 1;
	}
}

size_t BMH_search(const char* str, size_t str_len, const char* substr, size_t substr_len, size_t shift[256], size_t id_part) {
	size_t i = 0;

	while (i <= str_len - substr_len) {
		alt_memcmp(str + i, substr, substr_len, i + 1 + id_part);
		i += shift[(size_t)str[i + substr_len - 1] % 256];
	}

	return str_len - i;
}

void alt_memcmp(const char* str, const char* substr, size_t substr_len, size_t i) {
	int i1 = (int)substr_len - 1;

	while (i1 >= 0) {
		printf("%d ", (int)i + i1);

		if (str[i1] == substr[i1])
			i1 -= 1;
		else
			break;
	}
}
