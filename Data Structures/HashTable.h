#pragma once
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct hashTable *HashTable;

typedef struct slot *Slot;

HashTable initHashTable(int size);

HashTable insertHashTable(HashTable t, char *key, void* data, int dataSize);

Slot getSlot(HashTable table, char *key);

void *getSlotData(Slot e);

int getSlotDataSize(Slot e);

Slot setSlotData(Slot s, void *data, int dataSize);

int getHashTableSize();

void freeHashTable(HashTable h);