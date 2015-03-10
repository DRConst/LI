#include <stdlib.h>
#include <stdio.h>



typedef struct heap_str *Heap;
typedef int Elem;
int insertHeap(Heap h, Elem x);
Heap newheap(int size);
int extractMin(Heap h, Elem *x);