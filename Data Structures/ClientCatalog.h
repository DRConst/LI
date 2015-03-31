#pragma once
#include "BST.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
typedef struct clientCatalog
{
	int used;
	intBST ***Cat;
}ClientCatalog;

typedef struct client
{
	char *name;
	void **data;
	int *dataSize;
}Client;
ClientCatalog *initClientCatalog();
ClientCatalog *insertClient(ClientCatalog *cat, char *client);
int existsClient(ClientCatalog *cat, char *product);
int getClientCount( ClientCatalog *clientCat );
Client *getClient(ClientCatalog *cat, char *client);
int freeClientCatalog(ClientCatalog *cat);

