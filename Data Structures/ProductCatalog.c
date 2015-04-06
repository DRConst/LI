#include "ProductCatalog.h"
#include <string.h>

typedef struct productCatalog
{
	int used;
	intBST ***Cat;
}ProductCatalog_s;

ProductCatalog_s *initProductCatalog()
{
	int i = 0; int j = 0;
	ProductCatalog_s *cat = malloc(sizeof(ProductCatalog_s));
	cat->Cat = malloc(sizeof(intBST**) * 26);
	for (i = 0; i < 26; i++)
	{
		cat->Cat[i] = malloc(sizeof(intBST*)*26);
		for (j = 0; j < 26; j++)
			cat->Cat[i][j] = NULL;
	}


	cat->used = 0;
	return cat;
}

int existsProduct( ProductCatalog_s *cat, char *product )
{
	return(getProduct(cat, product) != NULL);
}

int getProductCount( ProductCatalog_s *prodCat )
{
    return ( prodCat ) ? ( prodCat->used ) : -1 ;
}

Product *getProduct(ProductCatalog_s *cat, char *product)
{
	Product *pr = malloc(sizeof(Product));
	int key = atoi(product + 2);
	Node *n = getNode(cat->Cat[product[0] - 'A'][product[1] - 'A'], key);

	if (!n)
		return NULL;


	pr->name = malloc(sizeof(char)* 7);
	strcpy(pr->name, product);


	pr->data = &n->data;
	pr->dataSize = &(n->dataSize);
	return pr;
}

ProductCatalog_s *insertProduct(ProductCatalog_s *cat, char *product)
{
	char *idC = product + 2;
	intBST *b;
	int id = atoi(idC);
	b = cat->Cat[toupper(product[0]) - 'A'][toupper(product[1]) - 'A'];
	cat->Cat[toupper(product[0]) - 'A'][toupper(product[1]) - 'A'] = insertBST(b, id, NULL, 0);
	cat->used++;
	return cat;
}

int freeProductCatalog(ProductCatalog_s *cat)
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

char **getProductsByPrefix(ProductCatalog_s *cat, char t, int *count )
{
	char **toRet = NULL, buff[5];
	int *codes, i, j, used;
	int cnt = 0;

	for (i = 0; i < 26; i++)
	{
		if ( cat->Cat[ t - 'A' ][i] )
		{
			used = cat->Cat[ t - 'A' ][i]->used;
			codes = inOrderBST(cat->Cat[ t - 'A'][i]);
			for (j = 0; j < used; j++)
			{
				toRet = realloc(toRet, sizeof(char*)*(cnt + 1));
				toRet[cnt] = malloc(sizeof(char) * 7);
				toRet[cnt][0] = t;
				toRet[cnt][1] = 'A' + i;
				sprintf( buff, "%d", codes[j] );
				buff[4] = '\0';
				strcpy(toRet[cnt] + 2, buff);
				cnt++;

			}
		}
	}

    *count = cnt;

	return toRet;
}




