#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "header.h"

int checkN(int count) {
    if (count < 0 || count > MAX_COUNT) {
        printf("bad number of points");
        return 1;
    }

    return 0;
}

int compPointX(const void* a, const void* b) {
    const struct Point* A = a;
    const struct Point* B = b;
    long long diff = (long long)A->x - B->x;

    return (diff > 0) ? 1 : (diff == 0) ? 0 : -1;
}

int compPointY(const void* a, const void* b) {
    const struct Point* A = a;
    const struct Point* B = b;
    long long diff = (long long)A->y - B->y;

    return (diff > 0) ? 1 : (diff == 0) ? 0 : -1;
}

struct Vector initVector(int count, int size) {
    struct Vector vector = createVector(count, size);

    for (int i = 0; i < count; ++i) {
        struct Point* point = (struct Point*)getVectorN(vector, i);

        if (scanf("%d %d", &point->x, &point->y) < 2) {
            delVector(&vector);
            printf("bad number of lines");
            exit(0);
        }

        ++vector.count;
    }

    return vector;
}

struct Vector createVector(int max, int size) {
    struct Vector vector = { 0, max, size, NULL };

    if (max > 0) {
        vector.arr = malloc((size_t)(max * size));

        if (vector.arr == NULL) {
            exit(1);
        }

        memset(vector.arr, 0, (size_t)(max * size));
    }

    return vector;
}

void* getVectorN(struct Vector vector, int n) {
    if (n >= vector.max) {
        exit(1);
    }

    return (char*)vector.arr + n * vector.size;
}

void delVector(struct Vector* vector) {
    if (vector->count != 0) {
        free(vector->arr);
    }

    vector->arr = NULL;
    vector->count = 0;
    vector->max = 0;
    vector->size = 0;
}

void assignVector(int size, const void* src, void* dest) {
    for (int i = 0; i < size; ++i) {
        ((char*)dest)[i] = ((char*)src)[i];
    }
}

int compPointL(const void* a, const void* b) {
    const struct Point* A = a;
    const struct Point* B = b;
    int diff = compPointX(A, B);

    if (diff == 0) {
        diff = compPointY(A, B);
    }

    return (diff > 0) ? 1 : (diff == 0) ? 0 : -1;
}

int compPointU(const void* a, const void* b) {
    const struct Point* A = a;
    const struct Point* B = b;
    int diff = compPointX(B, A);
    
    if (diff == 0) {
        diff = compPointY(B, A);
    }

    return (diff > 0) ? 1 : (diff == 0) ? 0 : -1;
}

struct Point findMin(struct Vector vector) {
    struct Point min = { INT_MAX, INT_MAX };

    for (int i = 0; i < vector.count; ++i) {
        char compare = compPointX(getVectorN(vector, i), &min) == 0 && compPointY(getVectorN(vector, i), &min) == -1;

        if (compPointX(getVectorN(vector, i), &min) == -1 || compare) {
            min = *((struct Point*)getVectorN(vector, i));
        }
    }

    return min;
}

struct Point findMax(struct Vector vector) {
    struct Point max = { INT_MIN, INT_MIN };

    for (int i = 0; i < vector.count; ++i) {
        char compare = compPointX(&max, getVectorN(vector, i)) == 0 && compPointY(&max, getVectorN(vector, i)) == -1;

        if (compPointX(&max, getVectorN(vector, i)) == -1 || compare) {
            max = *((struct Point*)getVectorN(vector, i));
        }
    }

    return max;
}

long double vectorMult(struct Point a, struct Point b, struct Point c) {
    long double dx1 = (long double)b.x - a.x;
    long double dx2 = (long double)c.x - a.x;
    long double dy1 = (long double)b.y - a.y;
    long double dy2 = (long double)c.y - a.y;

    return (dx1 * dy2) - (dy1 * dx2);
}

char rotCheck(struct Point a, struct Point b, struct Point c) {
    return vectorMult(a, b, c) > 0;
}

struct Vector createVectorL(struct Vector vector, struct Point min, struct Point max) {
    struct Vector set = createVector(vector.count, vector.size);
    int index = 0;

    for (int i = 0; i < vector.count; ++i) {
        long double mult = vectorMult(min, max, *((struct Point*)getVectorN(vector, i)));
        
        if (mult < 0) {
            assignVector(vector.size, getVectorN(vector, i), getVectorN(set, index));
            ++index;
        }
    }

    assignVector(vector.size, &min, getVectorN(set, index));
    assignVector(vector.size, &max, getVectorN(set, index + 1));
    
    set.count = index + 2;

    return set;
}

struct Vector createVectorU(struct Vector vector, struct Point min, struct Point max) {
    struct Vector set = createVector(vector.count, vector.size);
    int index = 0;

    for (int i = 0; i < vector.count; ++i) {
        long double mult = vectorMult(min, max, *((struct Point*)getVectorN(vector, i)));
        
        if (mult > 0) {
            assignVector(vector.size, getVectorN(vector, i), getVectorN(set, index));
            ++index;
        }
    }

    assignVector(vector.size, &min, getVectorN(set, index));
    assignVector(vector.size, &max, getVectorN(set, index + 1));
    
    set.count = index + 2;

    return set;
}

struct Stack GrahamAlg(struct Vector vector, int (*comp)(const void*, const void*)) {
    struct Stack stack = createStack(vector.count, vector.size);

    if (vector.count == 0) {
        return stack;
    }
    else if (vector.count == 1) {
        pushStack(vector.arr, &stack);
        return stack;
    }

    qsort(vector.arr, vector.count, vector.size, comp);

    pushStack(getVectorN(vector, 0), &stack);
    pushStack(getVectorN(vector, 1), &stack);

    for (int i = 2; i < vector.count; ++i) {
        while (stack.count > 1 && !rotCheck(*((struct Point*)topStack(stack)), *((struct Point*)getVectorN(vector, i)), *((struct Point*)nextTopStack(stack)))) {
            popStack(&stack);
        }

        pushStack(getVectorN(vector, i), &stack);
    }

    return stack;
}

void AndrewAlg(struct Vector vector) {
    if (vector.count == 0) {
        return;
    }

    if (vector.count == 1) {
        struct Point* point = (struct Point*)vector.arr;

        if (printf("%d %d\n", point->x, point->y) == EOF) {
            exit(1);
        }

        return;
    }

    struct Point min = findMin(vector);
    struct Point max = findMax(vector);

    struct Vector vectorL = createVectorL(vector, min, max);
    struct Stack stackL = GrahamAlg(vectorL, compPointL);
    
    delVector(&vectorL);
    popStack(&stackL);
    printStack(stackL);
    delStack(&stackL);

    struct Vector vectorU = createVectorU(vector, min, max);
    struct Stack stackU = GrahamAlg(vectorU, compPointU);
    
    delVector(&vectorU);
    popStack(&stackU);
    printStack(stackU);
    delStack(&stackU);
}
