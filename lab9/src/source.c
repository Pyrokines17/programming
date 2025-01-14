#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "header.h"

int checkN(int n) {
	if (n < 0 || n > 5000) {
		printf("bad number of vertices");
		return 1;
	}

	return 0;
}

int checkSF(int s, int f, int n) {
	if (s < 1 || s > n || f < 1 || f > n) {
		printf("bad vertex");
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

int check(int begin, int end, llint len, int n) {
	if (begin < 1 || begin > n || end < 1 || end > n) {
		printf("bad vertex");
		return 1;
	}

	if (len < 0 || len > INT_MAX) {
		printf("bad length");
		return 1;
	}

	return 0;
}

int readGraph(struct Matrix* graph, int graphSize, int edgeCount) {
	graph->size = graphSize;
	graph->data = (int*)malloc(graphSize * graphSize * sizeof(int));

	if (graph->data == NULL) {
		exit(1);
	}

	for (int i = 0; i < graphSize; ++i) {
		for (int j = 0; j < graphSize; ++j) {
			graph->data[i * graph->size + j] = -1;
		}
	}

	for (int k = 0; k < edgeCount; ++k) {
		int begin = 1,
			end = 1;
		llint len = 0;

		if (scanf("%d %d %lld", &begin, &end, &len) < 3) {
			printf("bad number of lines");
			free(graph->data);
			return 0;
		}

		if (check(begin, end, len, graphSize)) {
			free(graph->data);
			return 0;
		}

		begin--;
		end--;
		graph->data[begin * graph->size + end] = (int)len;
		graph->data[end * graph->size + begin] = (int)len;
	}

	return 1;
}

void setPath(struct Matrix* graph, int graphSize, int start, int* used, llint* best, int* parent) {
	const llint INF = (llint)INT_MAX * ((llint)graphSize + (llint)1);

	for (int i = 0; i < graphSize; i++) {
		best[i] = INF;
		used[i] = -1;
	}

	best[start] = 0;

	for (int i = 0; i < graphSize; ++i) {
		int v = -1;

		for (int j = 0; j < graphSize; ++j) {
			if (used[j] == -1 && (v == -1 || best[j] < best[v])) {
				v = j;
			}
		}

		if (v == -1 || best[v] == INF) {
			break;
		}

		used[v] = 1;

		for (int j = 0; j < graphSize; ++j) {
			if (getMatrix(graph, v, j) != -1 && v != j) {
				int ts = j;
				llint tf = getReal(getMatrix(graph, v, j));
				
				if (best[v] + tf < best[ts]) {                          
					best[ts] = best[v] + tf;                            
					parent[ts] = v;
				}
			}
		}
	}
}

int getMatrix(struct Matrix* g, int a, int b) { 
	return g->data[a * g->size + b];
}

llint getReal(int a) {
	if (a == -2) {
		return ((llint)INT_MAX + (llint)1);
	}

	return a;
}


void printAll(int graphSize, int* used, llint* best) {
	for (int i = 0; i < graphSize; ++i) {
		if (!used[i] || used[i] == -1) {
			printf("oo ");
		}
		else if (best[i] > (llint)INT_MAX) {
			printf("INT_MAX+ ");
		}
		else {
			printf("%lld ", best[i]);
		}
	}
}

void printFinish(struct Matrix* graph, int graphSize, int start, int finish, int* used, llint* best, int* parent, int* error) {
	if (!used[finish] || used[finish] == -1) {
		printf("\nno path");
	}
	else {
		struct Vector res = initVector(error);

		if (*error == 1) {
			return;
		}

		pushArr(&res, finish, 0, error);

		if (*error == 1) {
			return;
		}

		int v = finish;

		while (v != start) {
			pushArr(&res, parent[v], 0, error);

			if (*error == 1) {
				return;
			}

			v = parent[v];
		}
		
		int check = 0;

		if (best[finish] > (llint)INT_MAX) {
			for (int i = 0; i < graphSize; ++i) {
				used[i] = 0;
			}

			for (int j = 1; j < res.size - 1; ++j) {
				dfsCheck(graph, used, start, res.dataA[j], j);

				if (used[finish] == j) {
					printf("\noverflow");
					check = 1;
				}
			}
		}

		if (!check) {
			printf("\n");

			for (int i = 0; i < res.size; i++) {
				printf("%d ", res.dataA[i] + 1);
			}
		}

		free(res.dataA);
		free(res.dataB);
	}

}

void dfsCheck(struct Matrix* graph, int* used, int v, int deleted, int iter) { 
	used[v] = iter;

	for (int i = 0; i < graph->size; ++i) {
		int to = i;

		if (getMatrix(graph, v, i) != -1 && to != v && to != deleted && used[to] != iter)
			dfsCheck(graph, used, to, deleted, iter);
	}
}

void pushArr(struct Vector* vector, int a, int b, int* error) { 
	vector->size++;

	if (vector->size >= vector->buf) {
		vector->buf += 10;

		if (!(vector->dataA = (int*)realloc(vector->dataA, vector->buf * sizeof(int)))) {
			*error = 1;
			return;
		}

		if (!(vector->dataB = (int*)realloc(vector->dataB, vector->buf * sizeof(int)))) {
			*error = 1;
			return;
		}
	}

	vector->dataA[vector->size - 1] = a;
	vector->dataB[vector->size - 1] = b;
}

struct Vector initVector(int* error) { 
	struct Vector vector;

	vector.size = 0;
	vector.buf = 10;

	if (!(vector.dataA = (int*)malloc(vector.buf * sizeof(int)))) {
		*error = 1;
		return vector;
	}

	if (!(vector.dataB = (int*)malloc(vector.buf * sizeof(int)))) {
		*error = 1;
		return vector;
	}

	return vector;
}
