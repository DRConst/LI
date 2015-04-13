#include "ClientCatalog.h"

typedef struct clientCatalog
{
	int used;
	intBST ***Cat;
}*ClientCatalog_s;

ClientCatalog_s initClientCatalog()
{
	int i = 0; int j = 0;
	ClientCatalog_s cat = malloc(sizeof(ClientCatalog_s));
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

int freeClientCatalog(ClientCatalog_s cat)
{
	int i, j;

	for (i = 0; i < 26; i++)
	{
		for (j = 0; j < 26; j++)
		{
			freeBST(cat->Cat[i][j]);

		}
	}
	free(cat->Cat);
	free(cat);
	cat = NULL;
	return 1;
}

int existsClient(ClientCatalog_s cat, char *Client)
{
	return(getClient(cat, Client) != NULL);
}

Client getClient(ClientCatalog_s cat, char *client)
{
	Client cl = malloc(sizeof(struct client));
	int key = atoi(client + 2);
	Node *n = getNode(cat->Cat[client[0] - 'A'][client[1] - 'A'], key);

	if (!n)
		return NULL;


	cl->name = malloc(sizeof(char)* 7);
	strcpy(cl->name, client);


	cl->data = &n->data;
	cl->dataSize = &n->dataSize;
	return cl;
}

int getClientCount( ClientCatalog_s clientCat )
{
    return ( clientCat ) ? ( clientCat->used ) : -1 ;
}


ClientCatalog_s insertClient(ClientCatalog_s cat, char *client)
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

StringList getClientsByPrefix(ClientCatalog_s cat, char t )
{
	char buff[6];
	int *codes, i, j, used;
	StringList l = initStringList();
	for (i = 0; i < 26; i++)
	{
		if (cat->Cat[ t - 'A' ][i])
		{
			used = cat->Cat[ t - 'A' ][i]->used;
			codes = inOrderBST(cat->Cat[ t - 'A' ][i]);
			for (j = 0; j < used; j++)
			{
			    sprintf( buff, "%c%c%d", t, 'A' + i, codes[j] );
			    l = insertStringList( l, buff, 6 );

			}
		}
	}

	return l;
}




