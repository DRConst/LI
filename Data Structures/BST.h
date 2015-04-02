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

int getNodeData(Node *n, void **data, int *dataSize);
intBST *initBST();
intBST *insertBST(intBST *b, int elem, void *data, int dataSize);
int *inOrderBST(intBST *b);
Node *getNode(intBST *b, int key);
int freeBST(intBST *b);