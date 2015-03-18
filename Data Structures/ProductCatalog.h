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


ProductCatalog *initProductCatalog(ProductCatalog *cat);
ProductCatalog *insertProduct(ProductCatalog *cat, char *product);