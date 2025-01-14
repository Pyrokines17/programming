#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main(void) {
	int graphSize = 0,
		edgeCount = 0,
		begin = 1,
		end = 1,
		len = 0;

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

	if (graphSize == 1 && edgeCount == 0) {
		return 0;
	}

	struct Node* nodes = (struct Node*)malloc((size_t)(graphSize - 1) * sizeof(struct Node));

	if (nodes == NULL) {
		return 1;
	}

	struct Edge* edges = (struct Edge*)malloc(edgeCount * sizeof(struct Edge));

	if (edges == NULL) {
		free(nodes);
		return 1;
	}

	for (int i = 0; i < edgeCount; ++i) {
		if (scanf("%d %d %d", &begin, &end, &len) < 3) {
			printf("bad number of lines");
			free(nodes);
			free(edges);
			return 0;
		}

		if (check(begin, end, len, graphSize) == 1) {
			free(nodes);
			free(edges);
			return 0;
		}

		fillEdge(begin, end, len, &edges[i]);
	}

	qsort(edges, edgeCount, sizeof(struct Edge), cmp);

	int* parent = (int*)malloc(graphSize * sizeof(int));

	if (parent == NULL) {
		free(nodes);
		free(edges);
		return 1;
	}

	int* rank = (int*)malloc(graphSize * sizeof(int));

	if (rank == NULL) {
		free(nodes);
		free(edges);
		free(parent);
		return 1;
	}

	for (int i = 0; i < graphSize; ++i) {
		parent[i] = i;
		rank[i] = 0;
	}

	int edgesCount = 0;

	for (int i = 0; i < edgeCount; ++i) {
		int start = find(parent, edges[i].bPoint - 1);
		int finish = find(parent, edges[i].ePoint - 1);

		if (start != finish) {
			nodes[edgesCount].bPoint = edges[i].bPoint;
			nodes[edgesCount].ePoint = edges[i].ePoint;
			unite(parent, rank, start, finish);
			edgesCount++;

			if (edgesCount == graphSize - 1) {
				break;
			}
		}
	}

	if (edgesCount != graphSize - 1) {
		printf("no spanning tree");
	}
	else {
		for (int i = 0; i < graphSize - 1; ++i) {
			printf("%d %d\n", nodes[i].bPoint, nodes[i].ePoint);
		}
	}

	free(nodes);
	free(edges);
	free(parent);
	free(rank);

	return 0;
}
