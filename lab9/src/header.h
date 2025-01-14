#pragma once

typedef long long int llint;

struct Matrix {
	int size;
	int* data;
};

struct Vector {
	int size;
	int buf;
	int* dataA;
	int* dataB;
};

int checkN(int n);
int checkSF(int s, int f, int n);
int checkM(int m, int n);
int check(int begin, int end, llint len, int n);

int readGraph(struct Matrix* graph, int graphSize, int edgeCount);

void setPath(struct Matrix* graph, int graphSize, int start, int* used, llint* best, int* parent);

int getMatrix(struct Matrix* g, int a, int b);
llint getReal(int a);

void printAll(int graphSize, int* used, llint* best);
void printFinish(struct Matrix* graph, int graphSize, int start, int finish, int* used, llint* best, int* parent, int* error);

void dfsCheck(struct Matrix* graph, int* used, int v, int deleted, int iter);

void pushArr(struct Vector* vector, int a, int b, int* error);

struct Vector initVector(int* error);
