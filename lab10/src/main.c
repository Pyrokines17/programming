#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "header.h"

int main(void) {
    int count = 0;

    if (scanf("%d", &count) != 1) {
        printf("bad number of lines");
        return 0;
    }

    if (checkN(count) == 1) {
        return 0;
    }

    struct Vector vector = initVector(count, sizeof(struct Point));

    AndrewAlg(vector);
    delVector(&vector);

    return 0;
}
