#include "BST.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define UP(i) (i-1)/2
#define LEFT(i) 2*i+1
#define RIGHT(i) 2*i+2




intBST *initBST()
{
	intBST *b = (intBST*)malloc(sizeof(intBST));
	b->used = 0;
	b->root = NULL;
	return b;
}

Node *createNode(int elem, void *data, int dataSize)
{
	Node *toRet = malloc(sizeof(Node));
	toRet->key = elem;
	toRet->dataSize = dataSize;
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
	{
		node = createNode(elem, data, dataSize);
		return 1;
	}
		
	//if (elem == node->key)
		//return 1;
	if (elem <= node->key && node->l)
	{
		return auxInsert(node->l,elem,data,dataSize);
	}
	if (elem <= node->key && !node->l)
	{
		node->l = createNode(elem, data, dataSize);
		return 1;
	}
	if (elem > node->key && node->r)
	{
		return auxInsert(node->r, elem, data, dataSize);
	}
	if (elem > node->key && !node->r)
	{
		node->r = createNode(elem, data, dataSize);
		return 1;
	}


	return 1;
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
	int j, k;
	if (!n)
		return 0;
	inOrderAux(n->l, toRet, i);
	j = *i;
	toRet[*i] = n->key;
	k = toRet[*i];
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
Node *getNodeAux(Node *n,int key)
{
	if(!n)
	{
		return NULL;
	}
	if(n->key == key)
	{
		return n;
	}
	if(key < n->key)
	{
		return getNodeAux(n->l, key);
	}
	if(key > n->key)
	{
		return getNodeAux(n->r, key);
	}

	return NULL;
}

Node *getNode(intBST *b, int key)
{
	if(!b)
		return NULL;
	return getNodeAux(b->root,key);

}

int getNodeData(Node *n,void **data, int *dataSize)
{
	*dataSize = n->dataSize;
	*data = malloc(n->dataSize);
	memcpy(*data, n->data, n->dataSize);
	return 1;
}

void freeBSTAux(Node *n)
{
	if (!n)
		return;

	freeBSTAux(n->l);
	freeBSTAux(n->r);
	free(n->l);
	free(n->r);
	return;
}

int freeBST(intBST *b)
{
	if (!b)
		return 0;


	freeBSTAux(b->root);
	free(b->root);
	free(b);
	return 1;
}
/*
int main()
{
	intBST b;

	initBST(&b);
	char buff[] = "ASD\0";
	for (int i = 0; i < 100; i++)
	{
		int j = rand()%100;
		if(j==50){
		insertBST(&b, j, buff, 4);}
		else{
		insertBST(&b,j,NULL,0);}

	}
	int *order = inOrderBST(&b);

	for (int i = 0; i < b.used; i++)
	{
		printf("%d ", order[i]);
	}

	char c[4];int i;
	Node *n = getNode(&b,20);
	getNodeData(n,(void**)&c,&i);
	printf("%s", c);
}
*/
