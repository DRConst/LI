#pragma once
#include "BST.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
typedef struct clientCatalog
{
	int used;
	intBST ***Cat;
}ClientCatalog;


ClientCatalog *initClientCatalog();
ClientCatalog *insertClient(ClientCatalog *cat, char *client);
