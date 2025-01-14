#include <stdio.h>
#include "header.h"

size_t hash(const char* str, size_t str_len, int* degree) {
	size_t i = 0, 
			res = 0;

	while (i <= str_len - 1) {
		res = res + ((size_t)str[i] % 3) * *degree;
		*degree *= 3;
		i += 1;
	}
	*degree /= 3;

	return res;
}

size_t RK_search(const char* str, size_t str_len,const char* substr, size_t substr_hash, size_t substr_len, size_t id_part) {
	size_t i = 0,
		str_hash;
	int degree = 1;

	str_hash = hash(str, substr_len, &degree);

	while (i <= str_len - substr_len) {
		if (str_hash == substr_hash) check(str + i, substr, substr_len, i + 1 + id_part);
		str_hash = (str_hash - (size_t)*(str + i) % 3) / 3 + ((size_t)*(str + i + substr_len) % 3) * degree;
		i += 1;
	}

	return str_len - i;
}

size_t check(const char* str, const char* substr, size_t substr_len, size_t i) {
	size_t i1 = 0;

	while (i1 < substr_len) {
		printf("%zu ", i + i1);
		if (str[i1] == substr[i1]) i1 += 1;
		else return 0;
	}

	return 0;
}
