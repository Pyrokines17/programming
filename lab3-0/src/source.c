#include <stdio.h>
#include "header.h"

void heapsort(int n, int* arr) {
	int end = n;

	build_max_heap(arr, end);
	
	while (end != 1) {
		swap(&arr[0], &arr[end - 1]);
		end--;
		change_branches(arr, 0, end);
	}
}

void build_max_heap(int* arr, int end) {
	int i = (end - 2) / 2;

	while (i >= 0) {
		change_branches(arr, i--, end);
	}
}

void change_branches(int* arr, int i, int end) {
	int left = 2 * i + 1,
		right = 2 * i + 2,
		largest = i;

	if (left < end && arr[left] > arr[largest])
		largest = left;

	if (right < end && arr[right] > arr[largest])
		largest = right;

	if (largest != i) {
		swap(&arr[i], &arr[largest]);
		change_branches(arr, largest, end);
	}
}

void swap(int* a, int* b) {
	int c = *a;

	*a = *b;
	*b = c;
}
