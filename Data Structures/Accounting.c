#include "Accounting.h"


Sale *createSale(int month, int amnt, double price, char *product, char *client, char type)
{
	Sale *s = malloc(sizeof(Sale));
	if (!s)
		return NULL;
	s->amnt = amnt;
	s->month = month;
	s->price = price;
	s->product = malloc(sizeof(char)* 7);
	strcpy(s->product, product);
	s->client = malloc(sizeof(char)* 6);
	strcpy(s->client, client);
	return s;
}


Accounting *initAccounting()
{
	Accounting *acc = malloc(sizeof(Accounting));
	acc->cntEC = 0;
	acc->cntEP = 0;
	acc->sizeEC = 0;
	acc->sizeEP = 0;
	acc->sizeS = 0;
	acc->cntS = 0;
	acc->entriesCli = NULL;
	acc->entriesPr = NULL;
	acc->sales = NULL;
	return acc;
}

Accounting *addSale(Accounting *acc, ClientCatalog *cCat, ProductCatalog *pCat, Sale *sale)
{
	Client *cli;
	Product *pr;
	Entry *cliE, *prE;
	int i;
	if (!acc || !cCat || !pCat || !sale)
		return NULL;
	
	if (!existsClient(cCat, sale->client) || !existsProduct(pCat, sale->product))
		return NULL;


	cli = getClient(cCat, sale->client);
	pr = getProduct(pCat, sale->product);
	/* RESIZE */
	if (acc->cntEC == acc->sizeEC)
	{
		if (!acc->sizeEC)
			acc->sizeEC = 2;
		else{
			acc->sizeEC += acc->sizeEC;
		}

		acc->entriesCli = realloc(acc->entriesCli, acc->sizeEC);
	}

	if (acc->cntEP == acc->sizeEP)
	{
		if (!acc->sizeEP)
			acc->sizeEP = 2;
		else{
			acc->sizeEP += acc->sizeEP;
		}

		acc->entriesPr= realloc(acc->entriesPr, acc->sizeEP);
	}

	if (acc->cntS == acc->sizeS)
	{
		if (!acc->sizeS)
			acc->sizeS = 2;
		else{
			acc->sizeS += acc->sizeS;
		}

		acc->sales = realloc(acc->sales, acc->sizeS);
	}

	memcpy(&acc->sales[acc->cntS],sale,sizeof(Sale));

	//Check if product already has associated metadata
	pr = getProduct(pCat, sale->product);
	/*
	if (!pr)
		return NULL;
	if (pr->data != NULL && *pr->data != NULL)
	{
		i = *(int*)*pr->data;
		prE = &acc->entriesPr[i];
		if (prE->records[sale->month] == NULL)
		{
			prE->cntS[sale->month] = 1;
			prE->cnt[sale->month] = 1;
			prE->records[sale->month] = malloc(sizeof(int));
			prE->records[sale->month][0] = acc->cntS;
		}else{
			if (prE->cnt[sale->month] == prE->cntS[sale->month])
			{
				prE->records[sale->month] = realloc(prE->records[sale->month], prE->cntS[sale->month] * 2);
				prE->cntS[sale->month] += prE->cntS[sale->month];
			}
			prE->records[sale->month][prE->cnt[sale->month]] = acc->cntS;
			prE->cnt[sale->month]++;
			memcpy(&acc->entriesPr[acc->cntEP++], prE, sizeof(Entry));
		}
	}
	else
	{
		if (!pr->data)
			return NULL; //Something went seriously wrong

		*pr->data = (int*)malloc(sizeof(int));
		*(int*)*pr->data = acc->cntEP;
		prE = initEntry();
		if (prE->records[sale->month] == NULL)
		{
			prE->cntS[sale->month] = 1;
			prE->cnt[sale->month] = 1;
			prE->records[sale->month] = malloc(sizeof(int));
			prE->records[sale->month][0] = acc->cntS;
		}
		else{
			if (prE->cnt[sale->month] == prE->cntS[sale->month])
			{
				prE->records[sale->month] = realloc(prE->records[sale->month], prE->cntS[sale->month] * 2);
				prE->cntS[sale->month] += prE->cntS[sale->month];
			}
			prE->records[sale->month][prE->cnt[sale->month]] = acc->cntS;
			acc->cntS++;
			prE->cnt[sale->month]++;
			memcpy(&acc->entriesPr[acc->cntEP++], prE, sizeof(Entry));
		}

		acc->cntEP++;
	}*/

	if (!pr)
		return NULL;
	if (pr->data != NULL && *pr->data != NULL)
	{
		i = *(int*)*pr->data;
		prE = &acc->entriesPr[i];
	}
	else
	{
		if (!pr->data)
			return NULL; //Something went seriously wrong

		*pr->data = (int*)malloc(sizeof(int));
		*(int*)*pr->data = acc->cntEP;
		prE = initEntry();
		
	}
	if (prE->records[sale->month] == NULL)
	{
		prE->cntS[sale->month] = 1;
		prE->cnt[sale->month] = 1;
		prE->records[sale->month] = malloc(sizeof(int));
		prE->records[sale->month][0] = acc->cntS;
	}
	else{
		if (prE->cnt[sale->month] == prE->cntS[sale->month])
		{
			prE->records[sale->month] = realloc(prE->records[sale->month], prE->cntS[sale->month] * 2);
			prE->cntS[sale->month] += prE->cntS[sale->month];
		}
		prE->records[sale->month][prE->cnt[sale->month]] = acc->cntS;
		acc->cntS++;
		prE->cnt[sale->month]++;
		memcpy(&acc->entriesPr[acc->cntEP++], prE, sizeof(Entry));
	}
	
	cli = getClient(pCat, sale->product);
	

	if (!cli)
		return NULL;
	if (cli->data != NULL && *cli->data != NULL)
	{
		i = *(int*)*cli->data;
		cliE = &acc->entriesCli[i];
	}
	else
	{
		if (!cli->data)
			return NULL; //Something went seriously wrong

		*cli->data = (int*)malloc(sizeof(int));
		*(int*)*cli->data = acc->cntEP;
		cliE = initEntry();

	}
	if (cliE->records[sale->month] == NULL)
	{
		cliE->cntS[sale->month] = 1;
		cliE->cnt[sale->month] = 1;
		cliE->records[sale->month] = malloc(sizeof(int));
		cliE->records[sale->month][0] = acc->cntS;
	}
	else{
		if (cliE->cnt[sale->month] == cliE->cntS[sale->month])
		{
			cliE->records[sale->month] = realloc(cliE->records[sale->month], cliE->cntS[sale->month] * 2);
			cliE->cntS[sale->month] += cliE->cntS[sale->month];
		}
		cliE->records[sale->month][cliE->cnt[sale->month]] = acc->cntS;
		acc->cntS++;
		cliE->cnt[sale->month]++;
		memcpy(&acc->entriesCli[acc->cntEP++], cliE, sizeof(Entry));
	}

	
	
}



Entry *initEntry()
{
	Entry *e = malloc(sizeof(Entry));
	int i;
	//e->cnt = malloc(sizeof(int*)* 12);
	for (i = 0; i < 12; i++)
	{
		e->cnt[i] = 0;
		e->cntS[i] = 0;
	}
	e->units = 0;
	e->records = NULL;
	return e;
}

int getSalesCount(Accounting *acc)
{
	return acc ? acc->cntS : -1;
}