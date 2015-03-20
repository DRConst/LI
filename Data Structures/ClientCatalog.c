#include "ClientCatalog.h"


ClientCatalog *initClientCatalog(ClientCatalog *cat)
{
	int i = 0; int j = 0;
	if (!cat)
		cat = malloc(sizeof(ClientCatalog));
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





