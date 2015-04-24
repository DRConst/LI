#pragma once
#include "BST.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "StringList.h"
#include "HashTable.h"

typedef struct productCatalog *ProductCatalog;

typedef struct product *Product;

ProductCatalog initProductCatalog();
ProductCatalog insertProduct(ProductCatalog cat, char *product);
ProductCatalog freeProductCatalog(ProductCatalog cat);

int matchProductPattern( char *p );

int existsProduct( ProductCatalog cat, char *product );
int getProductCount( ProductCatalog prodCat );

Product getProduct(ProductCatalog cat, char* product);

StringList getProductsByPrefix(ProductCatalog cat, char t);

int getProductMetaData(Product pr, char *ID);
void setProductDataSize(Product pr, int size);
void setProductMetaData(Product pr, int x, char *ID);
char *getProductName(Product pr);
int getProductDataSize(Product pr);
int productHasMetaData(Product pr, char *ID);
void freeProduct(Product pr);