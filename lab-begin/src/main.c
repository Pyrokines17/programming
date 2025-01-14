#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <limits.h>

int summa(int* mass, int count);

int main(void) {
	long long per = 0;
	int mass[10] = { 0 },
		count = 0,
		i = 0,
		retValue = scanf("%d", &count);

	if (retValue == 0)
	{
		printf("%s\n", "bad input");
		return 0;
	}

	if (count < 1 || count > 10) {
		printf("%s\n", "bad input");
		return 0;
	}

	retValue = 0;

	while (i < count) {
		retValue += scanf("%lld", &per);

		if (per > INT_MAX || per < INT_MIN) {
			printf("%s", "bad input");
			return 0;
		}
		else {
			mass[i] = per;
			i += 1;
		}
	}

	if (retValue != count)
	{
		printf("%s\n", "bad input");
		return 0;
	}
	else {
		printf("%d\n", summa(mass, count));
		return 0;
	}
}

int summa(int* mass, int count) {
	int i1 = 0;
	long long sum = 0;

	while (i1 < count) {
		long long per1 = sum + mass[i1];
		if ((mass[i1] > 0 && sum < per1) || (mass[i1] < 0 && sum > per1)) {
			sum = per1;
			i1 += 1;
		}
		else {
			printf("%s\n", "overflow");
			return 0;
		}
	}
	
	if (sum > INT_MAX || sum < INT_MIN) {
		printf("%s\n", "overflow");
		return 0;
	}
	else {
		return sum;
	}
}
