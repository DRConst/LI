#include "../Data Structures/HashTable.h"

int main()
{
	HashTable t = initHashTable(5);
	insertHashTable(t, "asd", NULL, 0);
	Slot s = getSlot(t, "asd");
	int *a = malloc(sizeof(int));
	*a = 1;
	setSlotData(s, a, sizeof a);
	void *k = getSlotData(s);
	int j = (int)k;
	j = j;
}