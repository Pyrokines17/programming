#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "header.h"

int alt_strlen(char* str) {
	unsigned int i = 0;

	while (str[i] != '\0' && str[i] != '\n') {
		i++;
	}

	return i;
}

double StrToNumber(char* string, unsigned int base1, int* err) {
	double result = 0;
	unsigned int i = 0;

	while (i < 12 && string[i] != 0 && string[i] != '\n' && string[i] != '.') {
		int val = SymToNum(string[i], base1);

		if (val < 0) {
			*err = 1;
			return result;
		}

		result = result * base1 + val;
		i += 1;
	}

	if ('.' == string[i]) {
		double frac = 0;
		unsigned int end = alt_strlen(string) - 1;

		if (0 == i || i == end) {
			*err = 1;
			return result;
		}

		int id, 
			finish, 
			IdPoint = i;

		i += 1;
		finish = alt_strlen(string);
		id = finish - (i - IdPoint);

		while (i < 13 && string[i] != 0 && string[i] != '\n') {
			int val = SymToNum(string[id], base1);

			if (val < 0 || string[i] == '.') {
				*err = 1;
				return result;
			}

			frac = (frac + val) / base1;
			i += 1;
			id = finish - (i - IdPoint);
		}
		if (i >= 13 || string[i] == 0 || string[i] == '\n') result += frac;
	}

	return result;
}

char* NumberToStr(char* out, double x, unsigned int base2){
	unsigned int count = 0,
		i = 0;
	size_t APart;

	APart = (size_t)floor(x);
	x -= APart;
	char res[64];
	
	if (APart == 0) {
		res[i] = '0';
		count += 1;
	} 
	else {
		while (APart != 0) {
			res[i] = NumToSym(APart % base2);
			count += 1;
			APart /= base2;
			i += 1;
		}	
		i = 0;
	}

	while (count != 0) {
		out[i] = res[count - 1];
		count -= 1;
		i += 1;
	}
	
	if (x != 0) {
		out[i] = '.';
		i += 1;		
		while (x != 0 && count < 12) {
			x *= base2;
			int b = (int)floor(x);
			out[i] = NumToSym(b);
			x -= floor(x);
			count += 1;
			i += 1;
		}
	}

	return out;
}

int SymToNum(int Sym, int base1) {
	if (isdigit(Sym)) {
		if (Sym - '0' < base1) {
			return (Sym - '0');
		}
		else {
			return -1;
		}
	}
	else {
		if (tolower(Sym) - 'a' + 10 < base1) {
			return (tolower(Sym) - 'a' + 10);
		}
		else {
			return -1;
		}
	}
	return 0;
}

int NumToSym(int g) {
	if (g >= 0 && g < 10) {
		return (g + '0');
	}
	else if (g >= 10 && g < 17) {
		return (g - 10 + 'a');
	}
	return 0;
}
