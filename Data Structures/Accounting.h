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
