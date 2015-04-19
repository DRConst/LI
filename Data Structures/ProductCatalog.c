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
	void **data;
	int *dataSize;
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
	Node n = getNode(cat->Cat[product[0] - 'A'][product[1] - 'A'], key);

	if (!n)
		return NULL;


	pr->name = malloc(sizeof(char)* 7);
	strcpy(pr->name, product);


	pr->data = getDataAddr(n);
	pr->dataSize = getDataSizeAddr(n);
	return pr;
}

ProductCatalog_s insertProduct(ProductCatalog_s cat, char *product)
{
	char *idC = product + 2;
	intBST b;
	int id = atoi(idC);
	b = cat->Cat[toupper(product[0]) - 'A'][toupper(product[1]) - 'A'];
	cat->Cat[toupper(product[0]) - 'A'][toupper(product[1]) - 'A'] = insertBST(b, id, NULL, 0);
	cat->used++;
	return cat;
}

int freeProductCatalog(ProductCatalog_s cat)
{
	int i, j;

	for (i = 0; i < 26; i++)
	{
		for (j = 0; j < 26; j++)
		{
			freeBST(cat->Cat[i][j]);
		}
	}
	free(cat->Cat);
	free(cat);
	return 1;
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




int getProductMetaData(Product pr)
{
	if (!pr->data)
		return -1;
	return *(*(int **)pr->data);
}
void *getProductMetaDataAddr(Product pr)
{
	if (!pr->data)
		return NULL;
	return *pr->data;
}


int getProductDataSize(Product pr)
{
	if (pr)
		return(pr->dataSize ? *pr->dataSize : 0);
	return 0;
}

void allocProductMetaData(Product pr, int size)
{
	*(int**)pr->data = malloc(size);
}

void allocProductDataSize(Product pr, int size)
{
	pr->dataSize = malloc(size);
	*pr->dataSize = size;
}
void setProductDataSize(Product pr, int size)
{
	*pr->dataSize = size;
}

void setProductMetaData(Product pr, int x)
{
	*(*(int**)pr->data) = x;
}

char *getProductName(Product pr)
{
	return pr->name;
}
