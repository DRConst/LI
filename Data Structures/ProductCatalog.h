#pragma once
#include "BST.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

typedef struct productCatalog ProductCatalog;

typedef struct product
{
	char *name;
	void **data;
	int *dataSize;
}Product;

ProductCatalog *initProductCatalog();
ProductCatalog *insertProduct(ProductCatalog *cat, char *product);
int existsProduct( ProductCatalog *cat, char *product );
int getProductCount( ProductCatalog *prodCat );
Product *getProduct(ProductCatalog *cat, char* product);
int freeProductCatalog(ProductCatalog *cat);
char **getProductsByPrefix(ProductCatalog *cat, char t, int *count );
