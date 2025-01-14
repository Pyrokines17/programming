#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void quicksort(int* arr, int start, int end) {
	while (start < end) {
		int first_pivot,
			second_pivot;

		partition(arr, start, end, &first_pivot, &second_pivot);

		if ((first_pivot - start) > (end - second_pivot)) {
			quicksort(arr, second_pivot, end);
			end = first_pivot;
		}
		else {
			quicksort(arr, start, first_pivot);
			start = second_pivot;
		}
	}
}

void partition(int* arr, int start, int end, int* first_pivot, int* second_pivot) {
	int buf,
		mid = start,
		pivot_index = rand() % (end - start + 1) + start,
		pivot = arr[pivot_index];

	buf = arr[end];
	arr[end] = arr[pivot_index];
	arr[pivot_index] = buf;

	while (mid <= end) {
		if (arr[mid] < pivot) {
			buf = arr[mid];
			arr[mid] = arr[start];
			arr[start] = buf;
			start++;
			mid++;
		}
		else if (arr[mid] > pivot) {
			buf = arr[mid];
			arr[mid] = arr[end];
			arr[end] = buf;
			end--;
		}
		else 
			mid++;
	}

	*first_pivot = start - 1;
	*second_pivot = mid;
}
