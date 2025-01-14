#include <stdio.h>
#include "header.h"

int checkInput(int n, int m) {
    if (n < 0 || n > 2000) {
        printf("bad number of vertices");
        return 0;
    }

    if (m < 0 || m > n * (n + 1) / 2) {
        printf("bad number of edges");
        return 0;
    }

    return 1;
}

int checkVertex(int ver, int n) {
    if (ver < 1 || ver > n) {
        printf("bad vertex");
        return 0;
    }

    return 1;
}

int dfs(unsigned int* matrix, char* color, int ver, int n, int* arrVertices, int* id) {
    color[ver]++;

    for (int i = 1; i <= n; i++) {
        int part1 = matrix[(size_t)(ver * n + i) / (sizeof(unsigned int) * 8)];
        int part2 = (1 << ((sizeof(unsigned int) * 8) - ((size_t)(ver * n + i) % (sizeof(unsigned int) * 8))));

        if (part1 & part2) {
            if (color[i] == 1) {
                printf("impossible to sort");
                return 0;
            }
            else if (!color[i]) {
                    if (!dfs(matrix, color, i, n, arrVertices, id)) {
                        return 0;
                    }
            }
        }
    }

    color[ver]++;
    arrVertices[*id] = ver;
    (*id)++;

    return 1;
}

int topSort(unsigned int* matrix, char* color, int* arrVertices, int n) {
    int id = 0;

    for (int i = 1; i <= n; i++) {
        if (!color[i]) {
            if (!dfs(matrix, color, i, n, arrVertices, &id)) {
                return 0;
            }
        }
    }

    return 1;
}
