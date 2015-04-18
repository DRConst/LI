#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "ProductCatalog.h"
#include "ClientCatalog.h"
#include "minHeap.h"
#include "StringList.h"

typedef struct sale *Sale;

typedef struct productBuyers *ProductBuyers;

typedef struct entry Entry;

typedef struct accounting *Accounting;

typedef struct montly_purchases *Monthly_Purchases;

int orderAcc(Accounting acc, ProductCatalog pCat, ClientCatalog cCat);
Accounting initAccounting();
int addSale(Accounting acc, ClientCatalog cat, ProductCatalog pr, Sale sale);
Sale createSale(int month, int amnt, double price, char *product, char *client, char type);
int getSalesCount(Accounting acc);
Entry *initEntry();
int getProductSalesPerMonth(Accounting acc, Product prod, int month, int *nSalesP, int *nSalesN, double *totalProfit);
int getEntriesClientsCount(Accounting acc);
int getEntriesProductsCount(Accounting acc);
ProductBuyers productBuyers(Accounting acc, ProductCatalog pCat, ClientCatalog cCat, char *product);
Monthly_Purchases mostBoughtMonthlyProductsByClient(Accounting acc, ProductCatalog pCat, ClientCatalog cCat, char *client, int month);
StringList yearRoundClients(Accounting acc, ProductCatalog pCat, ClientCatalog cCat);
StringList mostSoldProducts(Accounting acc, ProductCatalog pCat, ClientCatalog cCat, int N);
StringList productsWithoutPurchases(Accounting acc);
StringList clientsWithoutPurchases(Accounting acc);

Monthly_Purchases initMonthlyPurchases();
Monthly_Purchases registerMonthlyPurchase(Monthly_Purchases mp, char *product, int cnt);
char **getMonthlyPurchasesList(Monthly_Purchases mp);
int *getMonthlyPurchasesCounts(Monthly_Purchases mp);
int getMonthlyPurchasesSize(Monthly_Purchases mp);
