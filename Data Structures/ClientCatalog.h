#pragma once
#include "BST.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "StringList.h"

typedef struct clientCatalog *ClientCatalog;

typedef struct client *Client;

ClientCatalog initClientCatalog();
ClientCatalog insertClient(ClientCatalog cat, char *client);
int matchClientPattern( char *c );
int existsClient(ClientCatalog cat, char *client);
int getClientCount( ClientCatalog clientCat );
Client getClient(ClientCatalog cat, char *client);
int freeClientCatalog(ClientCatalog cat);
StringList getClientsByPrefix(ClientCatalog cat, char t );

int getClientMetaData(Client cli);
void *getClientMetaDataAddr(Client cli);
void allocClientMetaData(Client cli, int size);
void allocClientDataSize(Client cli, int size);
void setClientDataSize(Client cli, int size);
void setClientMetaData(Client cli, int x);
char *getClientName(Client cli);
int getClientDataSize(Client cli);
