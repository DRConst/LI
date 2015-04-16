#include <stdlib.h>
#include <stdio.h>

typedef struct heap_str *minHeap;
typedef struct elem *Elem;
int insertHeap(minHeap h, int key, void *data, int dataSize);
minHeap newHeap(int size);
Elem extractMin(minHeap h);
int getMinHeapSize(minHeap h);
int getMinHeapUsed(minHeap h);
int getUsed(minHeap h);
int getSize(minHeap h);
void* getElemDataAddr(Elem e);
int getElemKey(Elem e);
