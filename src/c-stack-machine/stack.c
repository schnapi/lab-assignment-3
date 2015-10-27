#include <stdio.h>
#include <stdlib.h>

#define STACK_MAX 1000

struct Stack {
    int items[STACK_MAX];
    int size;
};
typedef struct Stack Stack;

void init_s(Stack *S) {
    S->size = 0;
}

void push_s(Stack *S, int d) {
    if (S->size < STACK_MAX) {
        S->items[S->size++] = d;
    } else {
        fprintf(stderr, "The stack is full\n");
        exit(-1);
    }
}

int pop_s(Stack *S) {
    if (S->size == 0) {
        fprintf(stderr, "The stack is empty\n");
        exit(-1);
    } else {
        S->size--;
        return S->items[S->size];
    }
}