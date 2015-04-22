#include "ProductCatalog.h"
#include <string.h>

typedef struct productCatalog
{
	int used;
	intBST **Cat;
}*ProductCatalog_s;

struct product
{
	char *name;
	void *data;
	int dataSize;
};

ProductCatalog_s initProductCatalog()
{
	int i = 0; int j = 0;
	ProductCatalog_s cat = malloc(sizeof(*cat));
	cat->Cat = malloc(sizeof(intBST*) * 26);
	for (i = 0; i < 26; i++)
	{
		cat->Cat[i] = malloc(sizeof(intBST)*26);
		for (j = 0; j < 26; j++)
			cat->Cat[i][j] = NULL;
	}


	cat->used = 0;
	return cat;
}

int matchProductPattern( char *p )
{
    return ( isalpha( p[0] ) && isalpha( p[1] ) &&
          isdigit( p[2] ) && isdigit( p[3] ) &&
          isdigit( p[4] ) && isdigit( p[5] ) );
}

int existsProduct( ProductCatalog_s cat, char *product )
{
	return ( matchProductPattern(product) && ( getProduct(cat, product) != NULL ) );
}

int getProductCount( ProductCatalog_s prodCat )
{
    return ( prodCat ) ? ( prodCat->used ) : -1 ;
}

Product getProduct(ProductCatalog_s cat, char *product)
{
	Product pr = malloc(sizeof(struct product));
	int key = atoi(product + 2);
	Node n = getNode(cat->Cat[toupper(product[0]) - 'A'][toupper(product[1]) - 'A'], key);
	if (!n)
		return NULL;


	pr->name = malloc(sizeof(char)* 7);
	strcpy(pr->name, product);


	pr->data = getNodeData(n);
	pr->dataSize = getDataSize(n);

	return pr;
}

ProductCatalog_s insertProduct(ProductCatalog_s cat, char *product)
{
	char *idC = product + 2;
	intBST b;
	int id = atoi(idC);
	HashTable t = initHashTable(2);
	b = cat->Cat[toupper(product[0]) - 'A'][toupper(product[1]) - 'A'];
	cat->Cat[toupper(product[0]) - 'A'][toupper(product[1]) - 'A'] = insertBST(b, id, t, sizeof t);
	cat->used++;
	return cat;
}

ProductCatalog_s freeProductCatalog(ProductCatalog_s cat)
{
	int i, j;

	for (i = 0; i < 26; i++)
	{
		for (j = 0; j < 26; j++)
		{
			freeBST(cat->Cat[i][j]);
		}
		free(cat->Cat[i]);
	}
	free(cat->Cat);
	free(cat);
	cat = NULL;
	return cat;
}

StringList getProductsByPrefix(ProductCatalog_s cat, char t )
{
    char buff[7];
	int *codes, i, j, used;
	StringList l = initStringList();

	for (i = 0; i < 26; i++)
	{
		if ( cat->Cat[ t - 'A' ][i] )
		{
			used = getUsedBST(cat->Cat[ t - 'A' ][i]);
			codes = inOrderBST(cat->Cat[ t - 'A'][i]);
			for (j = 0; j < used; j++)
			{
			    sprintf( buff, "%c%c%d", t, 'A' + i, codes[j] );
			    l = insertStringList( l, buff, 7 );
			}
		}
	}

	return l;
}




int getProductMetaData(Product pr, char *ID)
{
	HashTable t;
	Slot s;
	if (!pr->data)
		return -1;
	t = (HashTable)pr->data;
	s = getSlot(t, ID);
	if (!s)
		return -1;
	return *(int *)getSlotData(s);
}

int getProductDataSize(Product pr)
{
	if (pr)
		return pr->dataSize;
	return 0;
}

void setProductDataSize(Product pr, int size)
{
	pr->dataSize = size;
}

void setProductMetaData(Product pr, int x, char *ID)
{
	HashTable t;
	Slot s;
	if (!pr->data)
		return;
	t = (HashTable)pr->data;
	s = getSlot(t, ID);

	if (!s)
	{
		insertHashTable(t, ID, &x, sizeof x);
	}else
		setSlotData(s, &x, sizeof x);
	return;
}

char *getProductName(Product pr)
{
	return pr->name;
}

int productHasMetaData(Product pr, char *ID)
{
	HashTable t;
	Slot s;
	if (!pr->data)
		return 0;
	t = (HashTable)pr->data;
	s = getSlot(t, ID);

	if (!s)
	{
		return 0;
	}
	else
		return 1;
}
