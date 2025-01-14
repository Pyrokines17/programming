#include <stdio.h>
#include "header.h"

void create_shift(const char* substr, size_t substr_len, size_t* shift) {
	size_t i = 1;

	while (i < substr_len) {
		size_t x = shift[i - 1];

		while (x > 0 && substr[i] != substr[x])
			x = shift[x - 1];

		if (substr[i] == substr[x])
			x++;

		shift[i] = x;
		i++;
	}
}

size_t search_KMP(const char* str, const char* substr, size_t str_len, size_t substr_len, size_t* shift, size_t id_part) {
	size_t i = 0;
	
	while (i + substr_len <= str_len) {
		size_t i1 = 0;

		if (str[i] == substr[i1]) {
			printf("%zu ", i + 1 + id_part);

			while (i1 < substr_len && str[i + i1] == substr[i1]) {
				i1++;
			}

			printf("%zu ", i1);

		}
		
		if (i1 != 0)
			i += i1 - shift[i1 - 1];
		else
			i++;
	}

	return str_len - i;
}
