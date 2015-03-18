#pragma once
typedef struct intNode_stc
{
	int key, dataSize;
	void *data;
	struct intNode_stc *l, *r;
}Node;

typedef struct intBST_stc
{
	int used;
	Node *root;
}intBST;


intBST *initBST(intBST *b);
intBST *insertBST(intBST *b, int elem, void *data, int dataSize);
int *inOrderBST(intBST *b);
