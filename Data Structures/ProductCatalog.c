#include "ProductCatalog.h"
#include <string.h>

ProductCatalog *initProductCatalog()
{
	int i = 0; int j = 0;
	ProductCatalog *cat = malloc(sizeof(ProductCatalog));
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

int existsProduct( ProductCatalog *cat, char *product )
{
    int key = atoi( product + 2 );

    printf("\n%d", key);
	return (getNode(cat->Cat[product[0] - 'A'][product[1] - 'A'], key) != NULL);

}


ProductCatalog *insertProduct(ProductCatalog *cat, char *product)
{
	char *idC = product + 2;
	intBST *b;
	int id = atoi(idC);
	b = cat->Cat[toupper(product[0]) - 'A'][toupper(product[1]) - 'A'];
	cat->Cat[toupper(product[0]) - 'A'][toupper(product[1]) - 'A'] = insertBST(b, id, NULL, 0);
	cat->used++;
	return cat;
}

int freeProductCatalog(ProductCatalog *cat)
{
	int i, j;

	for (i = 0; i < 26; i++)
	{
		for (j = 0; j < 26; j++)
		{
			freeBST(cat->Cat[i][j]);
		}
	}
}

/*
*/




