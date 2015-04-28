#include "BST.h"

#define UP(i) (i-1)/2
#define LEFT(i) 2*i+1
#define RIGHT(i) 2*i+2

struct intNode_stc
{
    int key, dataSize;
    void *data;
    struct intNode_stc *l, *r, *p;
};


struct intBST_stc
{
    int used;
    Node root;
};


intBST initBST()
{
    intBST b = malloc(sizeof *b);
    b->used = 0;
    b->root = NULL;
    return b;
}

Node createNode(int elem, void *data, int dataSize, Node p)
{
    Node toRet = malloc(sizeof(*toRet));
    toRet->key = elem;
    toRet->dataSize = dataSize;
    if (data)
    {
        /*toRet->data = malloc(dataSize);
        memcpy(toRet->data, data, dataSize);*/
        /*HashTable t = (HashTable)data;*/
        toRet->data = data;
    }
    else
        toRet->data = NULL;
    toRet->r = NULL;
    toRet->l = NULL;
    toRet->p = p;
    return toRet;
}
int auxInsert(Node node, int elem, void *data, int dataSize)
{
    if (!node)
    {
        node = createNode(elem, data, dataSize, NULL);
        return 1;
    }

    /*
    if (elem == node->key)
        return 1;
    */
    if (elem <= node->key && node->l)
    {
        return auxInsert(node->l,elem,data,dataSize);
    }
    if (elem <= node->key && !node->l)
    {
        node->l = createNode(elem, data, dataSize, node);
        return 1;
    }
    if (elem > node->key && node->r)
    {
        return auxInsert(node->r, elem, data, dataSize);
    }
    if (elem > node->key && !node->r)
    {
        node->r = createNode(elem, data, dataSize, node);
        return 1;
    }


    return 1;
}

intBST insertBST(intBST b, int elem, void *data, int dataSize)
{
    if (!b)
        b = initBST();
    if (!b->root)
        b->root = createNode(elem, data, dataSize, NULL);
    else
        auxInsert(b->root, elem, data, dataSize);
    b->used++;
    return b;
}

/*
intBST insertBST_it(intBST b, int elem, void *data, int dataSize)
{
	Node n;
	if (!b)
		b = initBST(NULL);
	if (!b->root)
		b->root = createNode(elem, data, dataSize, NULL);
	else
	{
		n = b->root;
		while (n)
		{
			if (elem <= n->key)
			{
				if (n->l)
				{
					n = n->l;
				}
				else
				{
					n->l = createNode(elem, data, dataSize,n);
					n = NULL;
				}
			}
			else
			{
				if(n->r)
				{
					n = n->r;
				}
				else
				{
					n->r = createNode(elem, data, dataSize,n);
					n = NULL;
				}
			}
		}
	}
	b->used++;
	return b;
}*/
int inOrderAux(Node n, int *toRet, int *i)
{
    if (!n)
        return 0;
    inOrderAux(n->l, toRet, i);
    toRet[*i] = n->key;
    *i += 1;
    inOrderAux(n->r, toRet, i);
    return 1;
}

int *inOrderBST(intBST b)
{
    int i = 0;
    int *toRet = malloc(sizeof(int) * b->used);
    inOrderAux(b->root, toRet, &i);
    return toRet;
}

/*
int *inOrderBST_it(intBST b)
{
	int *toRet = malloc(sizeof(int)* b->used);
	int  i = 0;
	Stack *s = initStack();
	Node current = b->root;
	int done = 0;
	while (!done) {
		if (current) {
			push(s,current);
			current = current->l;
		}
		else {
			if (s->cnt == 0) {
				done = 1;
			}
			else {
				pop(s, &current);
				toRet[i++] = current->key;
				current = current->r;
			}
		}
	}

	return toRet;


}*/
Node getNodeAux(Node n,int key)
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

Node getNode(intBST b, int key)
{
    if(!b)
        return NULL;
    return getNodeAux(b->root,key);

}
/*
int getNodeData(Node n,void **data, int *dataSize)
{
	*dataSize = n->dataSize;
	*data = malloc(n->dataSize);
	memcpy(*data, n->data, n->dataSize);
	return 1;
}*/

void freeBSTAux(Node n)
{
    if (!n)
        return;

    freeBSTAux(n->l);
    freeBSTAux(n->r);
    free(n->l);
    free(n->r);
    return;
}

int freeBST(intBST b)
{
    if (!b)
        return 0;
    freeBSTAux(b->root);
    free(b->root);
    free(b);
    return 1;
}

int getUsedBST(intBST b)
{
    return (!b ? 0 : b->used);
}

void *getNodeDataAddr(Node n)
{
    return (!n ? NULL : &n->data);
}

void *getNodeData(Node n)
{
    return (!n ? NULL : n->data);
}

void setNodeData(Node n, void *data, int dataSize)
{
    if (n->data)
        free(n->data);
    n->data = data;
    n->dataSize = dataSize;
}

int getDataSize(Node n)
{
    return (!n ? 0 : n->dataSize);
}
