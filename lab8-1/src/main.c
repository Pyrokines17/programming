#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "header.h"

int main(void) {
	int graphSize = 0,
		edgeCount = 0,
		begin = 1,
		end = 1;
	size_t len = 0;

	if (scanf("%d", &graphSize) < 1) {
		printf("bad number of lines");
		return 0;
	}

	if (checkN(graphSize) == 1) {
		return 0;
	}

	if (scanf("%d", &edgeCount) < 1) {
		printf("bad number of lines");
		return 0;
	}

	if (checkM(edgeCount, graphSize) == 1) {
		return 0;
	}

	unsigned int** graph = (unsigned int**)malloc(sizeof(unsigned int*) * graphSize);

	if (graph == NULL) {
		return 1;
	}

	for (int i = 0; i < graphSize; i++) {
		graph[i] = malloc(sizeof(unsigned int) * graphSize);
	}

	for (int i = 0; i < graphSize; i++) {
		for (int j = 0; j < graphSize; j++) {
			graph[i][j] = (unsigned int)1 + INT_MAX;
		}
	}

	for (int i = 0; i < edgeCount; i++) {
		if (scanf("%d %d %zu", &begin, &end, &len) < 3) {
			printf("bad number of lines");
			freeCells(graph, graphSize);
			free(graph);
			return 0;
		}

		if (check(begin, end, len, graphSize) == 1) {
			freeCells(graph, graphSize);
			free(graph);
			return 0;
		}

		graph[begin - 1][end - 1] = (unsigned int)len;
		graph[end - 1][begin - 1] = (unsigned int)len;
	}

	char error = 0;

	char* used = (char*)malloc(sizeof(char) * graphSize);
	int* vertex = (int*)malloc(sizeof(int) * 2);
	unsigned int* dst = (unsigned int*)malloc(sizeof(unsigned int) * graphSize);
	int* num = (int*)malloc(sizeof(int) * graphSize);

	if (vertex == NULL || dst == NULL || num == NULL || used == NULL) {
		error = 1;
	}

	if (!error) {
		prima(graphSize, used, dst, vertex, num, error, graph);
	}
	else {
		free(vertex);
	}

	freeMem(graph, graphSize, used, dst, num);

	return 0;
}
