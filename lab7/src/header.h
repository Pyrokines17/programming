#pragma once

int checkInput(int n, int m);
int checkVertex(int ver, int n); 
int dfs(unsigned int* matrix, char* color, int ver, int n, int* arrVertices, int* id);
int topSort(unsigned int* matrix, char* color, int* arrVertices, int n);
