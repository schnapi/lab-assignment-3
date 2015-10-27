#include "functions.h"

void print() {
    printf("%i\n", pop(s));
}

void push(int val) {
    push_s(stack, val);
}

int pop() {
    return pop_s(stack);
}

void compGT() {
    int op2 = pop(), op1 = pop();
    push(op1 > op2 ? 1 : 0);
}

void compLT() {
    compGE();
    push(!pop());
}

void compLE() {
    compGT();
    push(!pop());
}

void compGE() {
    int op2 = pop(), op1 = pop();
    push(op1 >= op2 ? 1 : 0);
}

void compNE() {
    compEQ();
    push(!pop());
}

void compEQ() {
    push(pop() == pop());
}

void sub() {
    int op2 = pop(), op1 = pop();
    push(op1 - op2);
}

void neg() {
    push(-pop());
}

void add() {
    push(pop() + pop());
}

void mul() {
    push(pop() * pop());
}

void divide() {
    int op2 = pop(), op1 = pop();
    push(op1 / op2);
}

void gcd() {
    int op2 = pop(), op1 = pop();
    while (op1 != op2) {
        if (op1 > op2) {
            op1 = op1 - op2;
        } else {
            op2 = op2 - op1;
        }
    }
    push(op1);
}

void fact() {
    int n = pop();
    int res = 1;
    if (n != 0) {
        while (n > 1) {
            res *= n--;
        }
    }
    push(res);
}

void lntwo() {
    int op1 = pop();
    int x = 1;
    int ln = 0;
    while (x < op1) {
        x = x * 2;
        ln++;
    }
    push(ln);
}