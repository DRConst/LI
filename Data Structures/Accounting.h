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

typedef struct csv_stats *CSV_Stats;

Accounting initAccounting();
Accounting addAccounting( Accounting acc, ClientCatalog cCat, ProductCatalog pCat,  Sale sale );
Accounting orderAcc( Accounting acc, ProductCatalog pCat, ClientCatalog cCat);

CSV_Stats getMonthsStats(Accounting acc);

char **getList1CsvStats(CSV_Stats s);
char **getList2CsvStats(CSV_Stats s);
int getCntCsvStats(CSV_Stats s);

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

int getTotalUnitsByClient( Accounting acc, Client cl );
int getMonthUnitsByClient( Accounting acc, Client cl, int month );

int getTotalUnitsByProduct( Accounting acc, Product pr );
int getMonthUnitsByProduct( Accounting acc, Product pr, int month );

int getAccountingCount( Accounting acc );

StringList getAccountingUnboughtProducts( Accounting acc );
