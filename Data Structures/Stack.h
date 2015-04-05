#pragma once
#include <stdlib.h>
typedef struct stack
{
	int *stack;
	int cnt, size;
}Stack;

Stack *initStack();
int push(Stack *s, int x);
int pop(Stack *s, int *x);