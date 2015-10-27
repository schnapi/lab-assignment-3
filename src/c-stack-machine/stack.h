#ifndef STACK_H
#define STACK_H

#define STACK_MAX 100

struct Stack {
    int data[STACK_MAX];
    int size;
};
typedef struct Stack Stack;

void init_s(Stack *S);
void push_s(Stack *S, int d);
int pop_s(Stack *S);

#endif