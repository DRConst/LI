#include "ClientCatalog.h"


ClientCatalog *initClientCatalog()
{
	int i = 0; int j = 0;
	ClientCatalog *cat = malloc(sizeof(ClientCatalog));
	cat->Cat = malloc(sizeof(intBST**) * 26);
	for (i = 0; i < 26; i++)
	{
		cat->Cat[i] = malloc(sizeof(intBST*) * 26);
		for (j = 0; j < 26; j++)
			cat->Cat[i][j] = NULL;
	}


	cat->used = 0;
	return cat;
}

int freeClientCatalog(ClientCatalog *cat)
{
	int i, j;

	for (i = 0; i < 26; i++)
	{
		for (j = 0; j < 26; j++)
		{
			freeBST(cat->Cat[i][j]);
		}
	}

	return 1;
}

int existsClient(ClientCatalog *cat, char *Client)
{
	return(getClient(cat, Client) != NULL);
}

Client *getClient(ClientCatalog *cat, char *client)
{
	Client *cl = malloc(sizeof(Client));
	int key = atoi(client + 2);
	Node *n = getNode(cat->Cat[client[0] - 'A'][client[1] - 'A'], key);

	if (!n)
		return NULL;


	cl->name = malloc(sizeof(char)* 7);
	strcpy(cl->name, client);


	cl->data = &n->data;
	cl->dataSize = n->dataSize;
	return cl;
}

int getClientCount( ClientCatalog *clientCat )
{
    return ( clientCat ) ? ( clientCat->used ) : -1 ;
}


ClientCatalog *insertClient(ClientCatalog *cat, char *client)
{
	char *idC = client + 2;
	intBST *b;
	int id = atoi(idC);
	b = cat->Cat[toupper(client[0]) - 'A'][toupper(client[1]) - 'A'];
	cat->Cat[toupper(client[0]) - 'A'][toupper(client[1]) - 'A'] = insertBST(b, id, NULL, 0);
	b = cat->Cat[toupper(client[0]) - 'A'][toupper(client[1]) - 'A'];
	cat->used++;
	return cat;
}





