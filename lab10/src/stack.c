#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

struct Stack createStack(int max, int size) {
    struct Stack stack = { 0, max, size, NULL };

    if (max > 0) {
        stack.arr = malloc((size_t)(max * size));

        if (stack.arr == NULL) {
            exit(1);
        }

        memset(stack.arr, 0, (size_t)(max * size));
    }

    return stack;
}

void* getStackN(struct Stack stack, int n) {
    if (n >= stack.max) {
        exit(1);
    }

    return (char*)stack.arr + n * stack.size;
}

void* topStack(struct Stack stack) {
    if (stack.count == 0) {
        exit(1);
    }

    return getStackN(stack, stack.count - 1);
}

void* nextTopStack(struct Stack stack) {
    if (stack.count < 2) {
        exit(1);
    }

    return getStackN(stack, stack.count - 2);
}

void pushStack(void* value, struct Stack* stack) {
    if (stack->count == stack->max) {
        exit(1);
    }

    assignStack(stack->size, value, getStackN(*stack, stack->count));
    ++stack->count;
}

void* popStack(struct Stack* stack) {
    if (stack->count == 0) {
        exit(1);
    }

    --stack->count;
    return getStackN(*stack, stack->count);
}

void delStack(struct Stack* stack) {
    if (stack->count != 0) {
        free(stack->arr);
    }

    stack->arr = NULL;
    stack->count = 0;
    stack->max = 0;
    stack->size = 0;
}

void assignStack(int size, const void* src, void* dest) {
    for (int i = 0; i < size; ++i) {
        ((char*)dest)[i] = ((char*)src)[i];
    }
}

void printStack(struct Stack stack) {
    while (stack.count != 0) {
        struct Point* point = (struct Point*)popStack(&stack);

        if (printf("%d %d\n", point->x, point->y) == EOF) {
            exit(1);
        }
    }
}
