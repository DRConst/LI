#include "BST.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define UP(i) (i-1)/2
#define LEFT(i) 2*i+1
#define RIGHT(i) 2*i+2




intBST *initBST(intBST *b)
{
	if (!b)
		b = (intBST*)malloc(sizeof(intBST));
	b->used = 0;
	b->root = NULL;
	return b;
}

Node *createNode(int elem, void *data, int dataSize)
{
	Node *toRet = malloc(sizeof(Node));
	toRet->key = elem;
	if (data)
	{
		toRet->data = malloc(dataSize);
		memcpy(toRet->data, data, dataSize);
	}
	else
		toRet->data = NULL;
	toRet->r = toRet->l = NULL;
	return toRet;
}
int auxInsert(Node *node, int elem, void *data, int dataSize)
{
	if (!node)
		node = createNode(elem, data, dataSize);
	if (elem == node->key)
		return 1;
	if (elem < node->key && node->l)
	{
		//node = node->l;
		return auxInsert(node->l,elem,data,dataSize);
	}
	if (elem < node->key && !node->l)
	{
		node->l = createNode(elem, data, dataSize);
		return 1;
	}
	if (elem > node->key && node->r)
	{
		//node = node->r;
		return auxInsert(node->r, elem, data, dataSize);
	}
	if (elem > node->key && !node->r)
	{
		node->r = createNode(elem, data, dataSize);
		return 1;
	}

	
}

intBST *insertBST(intBST *b, int elem, void *data, int dataSize)
{
	if (!b)
		b = initBST(NULL);
	if (!b->root)
		b->root = createNode(elem, data, dataSize);
	else
		auxInsert(b->root, elem, data, dataSize);
	b->used++;
	return b;
}

int inOrderAux(Node *n, int *toRet, int *i)
{
	if (!n)
		return 0;
	inOrderAux(n->l, toRet, i);
	toRet[*i] = n->key;
	*i += 1;
	inOrderAux(n->r, toRet, i);
	return 1;
}

int *inOrderBST(intBST *b)
{
	int i = 0;
	int *toRet = malloc(sizeof(int) * b->used);
	inOrderAux(b->root, toRet, &i);
	return toRet;
}
/*
int main()
{
	intBST b;

	initBST(&b);
	for (int i = 0; i < 100; i++)
		insertBST(&b, rand(time(NULL)), NULL, 0);

	int *order = inOrderBST(&b);

	for (int i = 0; i < b.used; i++)
	{
		printf("%d ", order[i]);
	}



}*/