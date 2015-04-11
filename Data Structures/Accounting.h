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
	void **data; int dataS, dataC;
}Sale;

typedef struct entry Entry;

typedef struct accounting *Accounting;


int orderAcc(Accounting acc);
Accounting initAccounting();
int addSale(Accounting acc, ClientCatalog cat, ProductCatalog pr, Sale *sale);
Sale *createSale(int month, int amnt, double price, char *product, char *client, char type);
int getSalesCount(Accounting acc);
Entry *initEntry();
int getProductSalesPerMonth( Accounting acc, Product prod, int month, int *nSalesP, int *nSalesN, double *totalProfit );
int getEntriesClientsCount( Accounting acc );
int getEntriesProductsCount( Accounting acc );

