#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "header.h"

void freeMem(unsigned int** graph, int graphSize, char* used, unsigned int* dst, int* num) {
	freeCells(graph, graphSize);
	free(graph);
	free(used);
	free(dst);
	free(num);
}

void freeCells(unsigned int** graph, int graphSize) {
	for (int i = 0; i < graphSize; i++) {
		free(graph[i]);
	}
}

void prima(int graphSize, char* used, unsigned int* dst, int* vertex, int* num, int error, unsigned int** graph) {
	for (int i = 0; i < graphSize; i++) {
		used[i] = 0;
		dst[i] = (unsigned int)INT_MAX + 1;
	}

	dst[0] = 0;
	vertex[0] = 1;

	int u = 1,
		count = 0;

	for (int i = 0; i < graphSize; i++) {
		long long int minDst = (long long int)INT_MAX + 1;

		for (int j = 0; j < graphSize; j++) {
			if (used[j] == 0 && dst[j] < minDst) {
				minDst = dst[j];
				u = j;
			}
		}

		vertex[count + 1] = u + 1;
		vertex[count] = num[u];
		count += 2;

		int* vertex1 = (int*)realloc(vertex, sizeof(int) * (size_t)(count + 2));

		if (vertex1 == NULL) {
			error = 1;
			break;
		}
		else {
			vertex = vertex1;
		}

		used[u] = 1;

		for (int v = 0; v < graphSize; v++) {
			if (dst[v] > graph[u][v]) {
				dst[v] = graph[u][v];
				num[v] = u + 1;
			}
		}
	}

	for (int i = 0; i < graphSize && !error; i++) {
		if (used[i] == 0) {
			printf("no spanning tree");
			error = 1;
			break;
		}
	}

	if (!error) {
		for (int i = 2; i < count; i += 2) {
			printf("%d ", vertex[i]);
			printf("%d\n", vertex[i + 1]);
		}
	}

	free(vertex);
}

int checkN(int n) {
	if (n < 0 || n > 5000) {
		printf("bad number of vertices");
		return 1;
	}

	if (n == 0) {
		printf("no spanning tree");
		return 1;
	}

	return 0;
}

int checkM(int m, int n) {
	if (m < 0 || m > n * (n - 1) / 2) {
		printf("bad number of edges");
		return 1;
	}

	return 0;
}

int check(int begin, int end, size_t len, int n) {
	if (begin < 1 || begin > n || end < 1 || end > n) {
		printf("bad vertex");
		return 1;
	}

	if (len > INT_MAX) {
		printf("bad length");
		return 1;
	}

	return 0;
}
