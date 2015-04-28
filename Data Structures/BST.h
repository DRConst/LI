#pragma once
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "HashTable.h"

typedef struct intNode_stc *Node;

typedef struct intBST_stc *intBST;

void *getNodeDataAddr(Node n);
intBST initBST();
intBST insertBST(intBST b, int elem, void *data, int dataSize);
/*intBST insertBST_it(intBST b, int elem, void *data, int dataSize);*/
int *inOrderBST(intBST b);
/*int *inOrderBST_it(intBST b);*/
Node getNode(intBST b, int key);
int freeBST(intBST b);
int getUsedBST(intBST b);
void *getDataAddr(Node n);
int getDataSize(Node n);
void *getNodeData(Node n);
void setNodeData(Node n, void *data, int dataSize);
