#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "ProductCatalog.h"
#include "ClientCatalog.h"
#include "minHeap.h"
#include "StringList.h"
#include "Sale.h"

typedef struct accounting *Accounting;

Accounting initAccounting();
Accounting addAccounting( Accounting acc, ClientCatalog cCat, ProductCatalog pCat,  Sale sale );
Accounting orderAcc( Accounting acc, ProductCatalog pCat, ClientCatalog cCat);

double getMonthProfitByProduct( Accounting acc, Product pr, int month );
double getMonthProfitByClient( Accounting acc, Client cl, int month );

double getTotalProfitByProduct( Accounting acc, Product pr );
double getTotalProfitByClient( Accounting acc, Client cl );

int getTotalSalesNByProduct( Accounting acc, Product pr );
int getMonthSalesNByProduct( Accounting acc, Product pr, int month );

int getMonthSalesNByClient( Accounting acc, Client cl, int month );
int getTotalSalesNByClient( Accounting acc, Client cl );

int getTotalSalesPByProduct( Accounting acc, Product pr );
int getMonthSalesPByProduct( Accounting acc, Product pr, int month );

int getMonthSalesPByClient( Accounting acc, Client cl, int month );
int getTotalSalesPByClient( Accounting acc, Client cl );

int getAccountingCount( Accounting acc );
