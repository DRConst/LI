#include "ClientCatalog.h"

struct client
{
	char *name;
	void *data;
	int dataSize;
};

typedef struct clientCatalog
{
	int used;
	intBST **Cat;
}*ClientCatalog_s;

ClientCatalog_s initClientCatalog()
{
	int i = 0; int j = 0;
	ClientCatalog_s cat = malloc(sizeof(*cat));
	cat->Cat = malloc(sizeof(intBST*) * 26);
	for (i = 0; i < 26; i++)
	{
		cat->Cat[i] = malloc(sizeof(intBST) * 26);
		for (j = 0; j < 26; j++)
			cat->Cat[i][j] = NULL;
	}


	cat->used = 0;
	return cat;
}

ClientCatalog_s freeClientCatalog(ClientCatalog_s cat)
{
	int i, j;

	for (i = 0; i < 26; i++)
	{
		for (j = 0; j < 26; j++)
		{
			freeBST(cat->Cat[i][j]);

		}
		free(cat->Cat[i]);
	}
	free(cat->Cat);
	free(cat);
	cat = NULL;
	return cat;
}

int matchClientPattern( char *c )
{
    return ( isalpha( c[0] ) && isalpha( c[1] ) &&
          isdigit( c[2] ) && isdigit( c[3] ) &&
          isdigit( c[4] ) );
}

int existsClient(ClientCatalog_s cat, char *client)
{

	return ( matchClientPattern(client) && ( getClient(cat, client) != NULL ) );
}

Client getClient(ClientCatalog_s cat, char *client)
{
	Client cl = malloc(sizeof(struct client));
	int key = atoi(client + 2);
	Node n = getNode(cat->Cat[client[0] - 'A'][client[1] - 'A'], key);
	if (!n)
		return NULL;


	cl->name = malloc(sizeof(char)* 7);
	strcpy(cl->name, client);


	cl->data = getNodeData(n);
	cl->dataSize = getDataSize(n);
	return cl;
}

int getClientCount( ClientCatalog_s clientCat )
{
    return ( clientCat ) ? ( clientCat->used ) : -1 ;
}


ClientCatalog_s insertClient(ClientCatalog_s cat, char *client)
{
	char *idC = client + 2;
	intBST b;
	int id = atoi(idC);
	HashTable t = initHashTable(2);
	b = cat->Cat[toupper(client[0]) - 'A'][toupper(client[1]) - 'A'];
	cat->Cat[toupper(client[0]) - 'A'][toupper(client[1]) - 'A'] = insertBST(b, id, t, sizeof t);
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
			used = getUsedBST(cat->Cat[ t - 'A' ][i]);
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




int getClientMetaData(Client cli, char *ID)
{
	HashTable t;
	Slot s;
	if (!cli->data)
		return -1;
	t = (HashTable)cli->data;
	s = getSlot(t, ID);
	if (!s)
		return -1;
	return *(int *)getSlotData(s);
}
int getClientDataSize(Client cli)
{
	if (cli)
		return cli->dataSize;
	return 0;
}

void setClientDataSize(Client cli, int size)
{
	cli->dataSize = size;
}

void setClientMetaData(Client cli, int x, char *ID)
{
	HashTable t;
	Slot s;
	if (!cli->data)
		return;
	t = (HashTable)cli->data;
	s = getSlot(t, ID);

	if (!s)
	{
		insertHashTable(t, ID, &x, sizeof x);
	}
	else
		setSlotData(s, &x, sizeof x);
	return;
}

char *getClientName(Client cli)
{
	return cli->name;
}

int clientHasMetaData(Client cli, char *ID)
{
	HashTable t;
	Slot s;
	if (!cli->data)
		return 0;
	t = (HashTable)cli->data;
	s = getSlot(t, ID);

	if (!s)
	{
		return 0;
	}
	else
		return 1;
}
