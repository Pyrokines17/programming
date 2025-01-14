#pragma once

struct Node {
	int bPoint;
	int ePoint;
};

struct Edge {
	int bPoint;
	int ePoint;
	int weight;
};

void fillEdge(int begin, int end, int len, struct Edge* edge);
int cmp(const void* a, const void* b);
int find(int* parent, int point);
void unite(int* parent, int* rank, int start, int finish);

int checkN(int n);
int checkM(int m, int n);
int check(int begin, int end, int len, int n);
