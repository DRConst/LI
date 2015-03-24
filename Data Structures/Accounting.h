#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "ProductCatalog.h"
#include "ClientCatalog.h"
typedef struct sale
{
	int month, amnt;
	double price;
	char *product, *client, type;
}Sale;

typedef struct entry
{
	int *cnt, cntS;
	int units;
	int **records; //Matrix Month x Index
}Entry;


typedef struct accounting
{
	int cntEC, cntEP, sizeEC, sizeEP, sizeS, cntS;
	Entry *entriesCli, *entriesPr;
	Sale *sales;
}Accounting;



Accounting *initAccounting();
Accounting *addSale(Accounting *acc, ClientCatalog *cat, ProductCatalog *pr, Sale *sale);
Sale *createSale(int month, int amnt, double price, char *product, char *client, char type);

Entry *initEntry();