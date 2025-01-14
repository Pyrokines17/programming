#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main(void) {
	int n = 0,
		i = 0;

	if (scanf("%d", &n) == 0 || n == 0)
		return 0;

	int* arr = (int*)calloc(n, sizeof(int));

	while (i < n) {
		if (scanf("%d", &arr[i]) == 0)
			return 0;
		i++;
	}

	quicksort(arr, 0, n - 1);
	i = 0;
	
	while (i < n){
		printf("%d ", arr[i]);
		i++;
	}

	free(arr);

	return 0;
}
