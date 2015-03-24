#pragma once
#include "BST.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
typedef struct productCatalog
{
	int used;
	intBST ***Cat;
}ProductCatalog;


ProductCatalog *initProductCatalog();
ProductCatalog *insertProduct(ProductCatalog *cat, char *product);
int existsProduct( ProductCatalog *cat, char *product );

int freeProductCatalog(ProductCatalog *cat);
