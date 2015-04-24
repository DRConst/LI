#pragma once
#include "BST.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "HashTable.h"
#include "StringList.h"

typedef struct clientCatalog *ClientCatalog;

typedef struct client *Client;

ClientCatalog initClientCatalog();
ClientCatalog insertClient(ClientCatalog cat, char *client);
ClientCatalog freeClientCatalog(ClientCatalog cat);

int matchClientPattern( char *c );

int existsClient(ClientCatalog cat, char *client);
int getClientCount( ClientCatalog clientCat );

Client getClient(ClientCatalog cat, char *client);
void freeClient(Client cl);

StringList getClientsByPrefix(ClientCatalog cat, char t );

int getClientMetaData(Client cli, char *ID);
void setClientDataSize(Client cli, int size);
void setClientMetaData(Client cli, int x, char *ID);
char *getClientName(Client cli);
int getClientDataSize(Client cli);
int clientHasMetaData(Client pr, char *ID);