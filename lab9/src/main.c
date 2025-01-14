#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main(void) {
	int graphSize = 0,
		start = 1,
		finish = 1,
		edgeCount = 0;

	if (scanf("%d", &graphSize) < 1) {
		printf("bad number of lines");
		return 0;
	}

	if (checkN(graphSize) == 1) {
		return 0;
	}

	if (scanf("%d %d", &start, &finish) < 2) {
		printf("bad number of lines");
		return 0;
	}

	if (checkSF(start, finish, graphSize) == 1) {
		return 0;
	}

	finish--;
	start--;

	if (scanf("%d", &edgeCount) < 1) {
		printf("bad number of lines");
		return 0;
	}

	if (checkM(edgeCount, graphSize) == 1) {
		return 0;
	}

	struct Matrix graph;
	int error = 0;

	if (!readGraph(&graph, graphSize, edgeCount)) {
		return 0;
	}

	llint* best = (llint*)malloc(graphSize * sizeof(llint));

	if (best == NULL) {
		free(graph.data);
		return 1;
	}

	int* used = (int*)malloc(graphSize * sizeof(int));

	if (used == NULL) {
		free(best);
		free(graph.data);
		return 1;
	}

	int* parent = (int*)malloc(graphSize * sizeof(int));

	if (parent == NULL) {
		free(best);
		free(used);
		free(graph.data);
		return 1;
	}

	setPath(&graph, graphSize, start, used, best, parent);
	printAll(graphSize, used, best);
	printFinish(&graph, graphSize, start, finish, used, best, parent, &error);

	free(best);
	free(used);
	free(parent);
	free(graph.data);

	return 0;
}
