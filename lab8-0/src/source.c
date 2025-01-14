#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void fillEdge(int begin, int end, int len, struct Edge* edge) {
	edge->bPoint = begin;
	edge->ePoint = end;
	edge->weight = len;
}

int cmp(const void* a, const void* b) {
	return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

int find(int* parent, int point) {
	if (parent[point] == point) {
		return point;
	}
	else {
		return parent[point] = find(parent, parent[point]);
	}
}

void unite(int* parent, int* rank, int start, int finish) {
	int sParent = find(parent, start);
	int fParent = find(parent, finish);

	if (sParent == fParent) {
		return;
	}

	if (rank[sParent] < rank[fParent]) {
		parent[sParent] = fParent;
	}
	else if (rank[sParent] > rank[fParent]) {
		parent[fParent] = sParent;
	}
	else {
		parent[fParent] = sParent;
		rank[sParent]++;
	}
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
	if (m < 0 || m > n * (n + 1) / 2) {
		printf("bad number of edges");
		return 1;
	}

	if (m < n - 1) {
		printf("no spanning tree");
		return 1;
	}

	return 0;
}

int check(int begin, int end, int len, int n) {
	if (begin < 0 || begin > n || end < 0 || end > n) {
		printf("bad vertex");
		return 1;
	}

	if (len < 0) {
		printf("bad length");
		return 1;
	}

	return 0;
}
