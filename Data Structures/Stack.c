#include "Stack.h"

Stack *initStack()
{
	Stack *toRet = malloc(sizeof(Stack));
	toRet->stack = malloc(sizeof(int)* 10);
	toRet->size = 10;
	toRet->cnt = 0;
	return toRet;
}



int push(Stack *s, int x)
{
	if (s->cnt == s->size)
	{
		s->size += s->size;
		int *tmp = realloc(s->stack, s->size * sizeof(int));
		if (!tmp)
			return 0;
		/* free(s->stack); */
		s->stack = tmp;
	}

	s->stack[s->cnt++] = x;
	return 1;
}

int pop(Stack *s, int *x)
{
	if (!x && !s && !s->stack && s->cnt < 1)
		return -1;
	*x = s->stack[s->cnt - 1];
	s->cnt--;
	return 1;
}
