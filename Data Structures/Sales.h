#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "ProductCatalog.h"
#include "ClientCatalog.h"
#include "minHeap.h"
#include "StringList.h"
#include "Sale.h"
typedef struct productBuyers *ProductBuyers;

typedef struct sales *Sales;

typedef struct montly_purchases *Monthly_Purchases;

Sales orderSales(Sales acc, ProductCatalog pCat, ClientCatalog cCat);
Sales initSales();
Sales addSale(Sales acc, ClientCatalog cat, ProductCatalog pr, Sale sale);
Sale createSale(int month, int amnt, double price, char *product, char *client, char type);
Sales freeSales(Sales acc);
int getSalesCount(Sales acc);
int getProductSalesPerMonth(Sales acc, Product prod, int month, int *nSalesP, int *nSalesN, double *totalProfit);
int getEntriesClientsCount(Sales acc);
int getEntriesProductsCount(Sales acc);
ProductBuyers productBuyers(Sales acc, ProductCatalog pCat, ClientCatalog cCat, char *product);
Monthly_Purchases mostBoughtMonthlyProductsByClient(Sales acc, ProductCatalog pCat, ClientCatalog cCat, char *client, int month);
StringList yearRoundClients(Sales acc, ProductCatalog pCat, ClientCatalog cCat);
StringList mostSoldProducts(Sales acc, ProductCatalog pCat, ClientCatalog cCat, int N);
StringList productsWithoutPurchases(Sales acc);
StringList clientsWithoutPurchases(Sales acc);

Monthly_Purchases initMonthlyPurchases();
Monthly_Purchases registerMonthlyPurchase(Monthly_Purchases mp, char *product, int cnt);
char **getMonthlyPurchasesList(Monthly_Purchases mp);
int *getMonthlyPurchasesCounts(Monthly_Purchases mp);
int getMonthlyPurchasesSize(Monthly_Purchases mp);


char ** getProductBuyersN(ProductBuyers pb);
char ** getProductBuyersP(ProductBuyers pb);
int getProductBuyersCntN(ProductBuyers pb);
int getProductBuyersCntP(ProductBuyers pb);
