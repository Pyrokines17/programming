#pragma once

#define MAX_COUNT 100000

struct Point {
    int x;
    int y;
};

struct Vector {
    int count;
    int max;
    int size;
    void* arr;
};

struct Stack {
    int count;
    int max;
    int size;
    void* arr;
};

int checkN(int count);

int compPointX(const void* a, const void* b);
int compPointY(const void* a, const void* b);

struct Vector initVector(int count, int size);
struct Vector createVector(int max, int size);
void* getVectorN(struct Vector vector, int n);
void delVector(struct Vector* vector);
void assignVector(int size, const void* src, void* dest);

struct Stack createStack(int max, int size);
void* getStackN(struct Stack stack, int n);
void* topStack(struct Stack stack);
void* nextTopStack(struct Stack stack);
void pushStack(void* value, struct Stack* stack);
void* popStack(struct Stack* stack);
void delStack(struct Stack* stack);
void assignStack(int size, const void* src, void* dest);
void printStack(struct Stack stack);

int compPointL(const void* a, const void* b);
int compPointU(const void* a, const void* b);

struct Point findMin(struct Vector vector);
struct Point findMax(struct Vector vector);

long double vectorMult(struct Point a, struct Point b, struct Point c);
char rotCheck(struct Point a, struct Point b, struct Point c);

struct Vector createVectorL(struct Vector vector, struct Point min, struct Point max);
struct Vector createVectorU(struct Vector vector, struct Point min, struct Point max);

struct Stack GrahamAlg(struct Vector vector, int (*comp)(const void*, const void*));
void AndrewAlg(struct Vector vector);
