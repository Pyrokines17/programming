#include <string.h>
#include "Header.h"

int next_permutation(char* permutation) {
	unsigned int len, 
		id, 
		i1 = 0;
	int ret = 0;
	char zam;

	len = (unsigned int)strlen(permutation) - 1;

	while (i1 < len) {
		if (permutation[len - (i1 + 1)] < permutation[len - i1]) {
			id = len - (i1 + 1);
			zam = permutation[id];
			permutation[id] = replacement(permutation, len, zam);
			ret = result(permutation, len, id);
			i1 = len;
		}
		else {
			i1 += 1;
		}
	}
	return ret;
}

char replacement(char* permutation, unsigned int len, char zam) {
	unsigned int i2 = 0;
	char zam1;

	while (i2 < len) {
		if (zam < permutation[len - i2]) {
			zam1 = permutation[len - i2];
			permutation[len - i2] = zam;
			return zam1;
		}
		else i2 += 1;
	}
	return 0;
}

int result(char* permutation, unsigned int len, unsigned int id) {
	unsigned int leni, 
		i3 = id + 1;

	leni = len;
	while (leni > id + 1 + (leni - id - 1) / 2) {
		char tmp = permutation[i3];

		permutation[i3] = permutation[leni];
		permutation[leni] = tmp;
		leni -= 1;
		i3 += 1;
	}
	return 1;
}

int check(char* permutation) {
	unsigned int finish, 
		i5 = 0;
	char CountNum[10] = { 0 };
	
	finish = (unsigned int)strlen(permutation);

	while (i5 < finish) {
		if (permutation[i5] - '0' >= 0 && permutation[i5] - '0' <= 9) {
			CountNum[permutation[i5] - '0'] += 1;
			if (CountNum[permutation[i5] - '0'] > 1) {
				return 1;
			}
			i5 += 1;
		}
		else {
			return 1;
		}
	}
	return 0;
}
