#pragma once
#include "BST.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "StringList.h"

typedef struct productCatalog *ProductCatalog;

typedef struct product
{
	char *name;
	void **data;
	int *dataSize;
}*Product;

ProductCatalog initProductCatalog();
ProductCatalog insertProduct(ProductCatalog cat, char *product);
int existsProduct( ProductCatalog cat, char *product );
int getProductCount( ProductCatalog prodCat );
Product getProduct(ProductCatalog cat, char* product);
int freeProductCatalog(ProductCatalog cat);
StringList getProductsByPrefix(ProductCatalog cat, char t);
