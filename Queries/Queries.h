#pragma once
#include "../Data Structures/ProductCatalog.h"
#include "../Data Structures/ClientCatalog.h"
#include <string.h>


char **query2(ProductCatalog *cat, char t, int *count );

char **query6(ClientCatalog *cat, char t, int *count);
