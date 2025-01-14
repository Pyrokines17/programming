#pragma once

void freeMem(unsigned int** graph, int graphSize, char* used, unsigned int* dst, int* num);
void freeCells(unsigned int** graph, int graphSize);

void prima(int graphSize, char* used, unsigned int* dst, int* vertex, int* num, int error, unsigned int** graph);

int checkN(int n);
int checkM(int m, int n);
int check(int begin, int end, size_t len, int n);
