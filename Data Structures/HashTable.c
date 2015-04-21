#include "HashTable.h"

typedef struct slot
{
	Slot n;
	char *key;
	void *data;
	int dataSize;
}*Slot_s;

typedef struct hashTable
{
	int size;
	Slot *slots;
}*hashTable_s;

typedef struct entry
{
	char *key;
	void *data;
	int dataSize;
}*Entry_s;

int hash(char*key)
{
	int i, len = strlen(key), h = 0;
	for (i = 0; i < len; i++)
	{
		h += pow(key[i], i);
	}
	return h;
}
HashTable initHashTable(int size)
{
	int i;
	HashTable  toRet = malloc(sizeof *toRet);
	if (!toRet)
		return NULL;
	toRet->slots = malloc(sizeof(Slot) * size);
	for (i = 0; i < size; i++)
		toRet->slots[i] = NULL;
	toRet->size = size;
	return toRet;
}

HashTable insertHashTable(HashTable h, char *key, void* data, int dataSize)
{
	int i = hash(key) % h->size;
	Slot s;

	if (!h->slots[i])
	{
		h->slots[i] = malloc(sizeof(struct slot));
		s = h->slots[i];
	}
	else
	{
		s = h->slots[i];
		while (s->n)
		{
			if (!strcmp(s->key, key))
				return NULL;
			s = s->n;
		}
		s->n = malloc(sizeof(struct slot));
		s = s->n;
	}
	s->key = malloc(sizeof(char) * (strlen(key) + 1));
	strcpy(s->key, key);
	if (data){
		s->data = malloc(dataSize);
		memcpy(s->data, data, dataSize);
		s->dataSize = dataSize;
	}
	else
	{
		s->data = NULL;
		s->dataSize = 0;
	}

	s->n = NULL;
	return h;

}

Slot getSlot(HashTable h, char *key)
{
	int i = hash(key) % h->size;
	Slot s = h->slots[i];
	if (!s)
	{
		return NULL;
	}
	else
	{
		while (s && strcmp(s->key,key))
		{
			s = s->n;
		}
	}
	return s;
}

int getSlotDataSize(Slot e)
{
	if (!e)
		return 0;
	return e->dataSize;
}

void *getSlotData(Slot s)
{
	if (!s)
		return NULL;
	return s->data;
}

Slot setSlotData(Slot s, void *data, int dataSize)
{
	if (!s)
		return NULL;

	if (s->data)
		free(s->data);
	s->data = malloc(dataSize);
	s->dataSize = dataSize;
	memcpy(s->data, data, dataSize);
	return s;
}

int getHashTableSize()
{
	return sizeof(struct hashTable);
}
