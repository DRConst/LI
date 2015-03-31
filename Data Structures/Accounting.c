#include "Accounting.h"


Sale *createSale(int month, int amnt, double price, char *product, char *client, char type)
{
	Sale *s = malloc(sizeof(Sale));
	if (!s)
		return NULL;
	s->amnt = amnt;
	s->month = month;
	s->price = price;
	s->product = malloc(sizeof(char)* 70);
	strcpy(s->product, product);
	s->client = malloc(sizeof(char)* 60);
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
int copySale(Sale **dest, Sale* src)
{
	if (dest == NULL)
		return 0;
	*dest = createSale(src->month, src->amnt, src->price, src->product, src->client, src->type);
	/*dest->amnt = src->amnt;
	//strcpy(dest->client,src->client);
	//strcpy(dest->product, src->product);
	dest->month = src->month;
	dest->price = src->price;
	dest->type = src->type;*/
}

int copyEntry(Entry **dest, Entry *src)
{
	if (!dest)
		return 0;
	*dest = (Entry*)malloc(sizeof(Entry));
	/*Entry *tmp = (*dest);*/
	memcpy((*dest)->cnt, src->cnt,12*sizeof(int));
	memcpy((*dest)->cntS, src->cntS,12*sizeof(int));
	(*dest)->units = src->units;

}

/*Accounting *addSale(Accounting *acc, ClientCatalog *cCat, ProductCatalog *pCat, Sale *sale)
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
	/* RESIZE 
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

	//memcpy(&acc->sales[acc->cntS],sale,sizeof(Sale));
	copySale(&acc->sales[acc->cntS], sale);
	
	//pr = getProduct(pCat, sale->product);
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
	}

	if (!pr)
		return NULL;
	if (pr->data != NULL && *pr->data != NULL)
	{
		i = *(int*)*pr->data;
		prE = acc->entriesPr[i];
	}
	else
	{
		if (!pr->data)
			return NULL; 

		*pr->data = (int*)malloc(sizeof(int));
		*(int*)*pr->data = acc->cntEP;
		prE = initEntry();
		memcpy(acc->entriesPr[acc->cntEP], prE, sizeof(Entry));
		
	}
//	prE = initEntry();
	
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
			return NULL; /*Something went seriously wrong

		*cli->data = (int*)malloc(sizeof(int));
		*(int*)*cli->data = acc->cntEP;
		cliE = initEntry();
		memcpy(&acc->entriesCli[acc->cntEC], cliE, sizeof(Entry));

	}
	cliE = initEntry();
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

	
	acc->cntS++;
}*/

Accounting *addSale(Accounting *acc, ClientCatalog *cCat, ProductCatalog *pCat, Sale *sale)
{
	/*Misc vars*/
		int i;

	/*Vars for reallocing*/
		Entry **reEC, **reEP;
		Sale **reS;

	/*Vars for product binding*/
		Product *pr;
		Entry *tE;
		Client *cl;

	/*Check if the sizes allow for insertion, if not realloc stuff*/

		if (acc->cntEC == acc->sizeEC)/*Client Entry array is full*/
		{
			if (!acc->sizeEC)
				acc->sizeEC = 2;
			else
				acc->sizeEC += acc->sizeEC;
			reEC = malloc(sizeof(Entry*)*acc->sizeEC);
			for (i = 0; i < acc->sizeEC/2; i++)
			{
				if (acc->entriesCli && acc->entriesCli[i])
					reEC[i] = acc->entriesCli[i];
				else
					reEC[i] = NULL;
			}
			for (i = acc->sizeEC / 2; i < acc->sizeEC; i++)
			{
				reEC[i] = NULL;
			}
			/*acc->sizeEC += acc->sizeEC;*/
			/*free(acc->entriesCli);*/
			acc->entriesCli = reEC;
			reEC = NULL;
		}

		if (acc->cntEP == acc->sizeEP)/*Product Entry array is full*/
		{

			if (!acc->sizeEP)
				acc->sizeEP = 2;
			else
				acc->sizeEP += acc->sizeEP;
			reEP = malloc(sizeof(Entry*)*acc->sizeEP);
			for (i = 0; i < acc->sizeEC / 2; i++)
			{
				if (acc->entriesPr && acc->entriesPr[i])
					reEP[i] = acc->entriesPr[i];
				else
					reEP[i] = NULL;
			}
			for (i = acc->sizeEP / 2; i < acc->sizeEP; i++)
			{
				reEP[i] = NULL;
			}
			/*acc->sizeEP += acc->sizeEP;*/
			/*free(acc->entriesPr);*/
			acc->entriesPr = reEP;
			reEP = NULL;
		}

		if (acc->cntS == acc->sizeS)/*Sales array is full*/
		{

			if (!acc->sizeS)
				acc->sizeS = 2;
			else
				acc->sizeS += acc->sizeS;
			reS = malloc(sizeof(Entry*)*acc->sizeS);
			for (i = 0; i < acc->sizeS/2; i++)
			{
				if (acc->sales && acc->sales[i])
					reS[i] = acc->sales[i];
				else
					reS[i] = NULL;
			}
			for (i = acc->sizeS / 2; i < acc->sizeS; i++)
			{
				reS[i] = NULL;
			}
			
			/*acc->sizeS += acc->sizeS;*/
			/*free(acc->sales);*/
			acc->sales = reS;
			reS = NULL;
		}

	/*Done size checking*/


	/*First add sale to the registry*/

		copySale(acc->sales, sale);

	/*Now bind the sale to the product*/
		pr = getProduct(pCat, sale->product);
		if (!pr)
			return NULL;
		cl = getClient(cCat, sale->client);
		if (!cl)
			return NULL;
		/*Check if the product already has an entry bound by checking metadata*/
			if (*pr->dataSize != 0)
			{
				i = *(*(int **)pr->data); /*Index of entriePr where the product is bound*/

				tE = acc->entriesPr[i];

				/*Check if there is space to add Entry, else realloc*/
					if (acc->entriesPr[i]->cnt[sale->month - 1] == acc->entriesPr[i]->cntS[sale->month - 1])
					{
						acc->entriesPr[i]->cntS[sale->month - 1] += acc->entriesPr[i]->cntS[sale->month - 1];
						realloc(acc->entriesPr[i]->records[sale->month - 1], acc->entriesPr[i]->cntS[sale->month - 1]);
					}
					acc->entriesPr[i]->records[sale->month - 1][acc->entriesPr[i]->cnt[sale->month - 1]] = acc->cntS;
					acc->entriesPr[i]->units += sale->amnt;

					/*copyEntry(&acc->entriesPr[i], tE);*/
			}/*Else create new Product Entry, update metadata*/else{
				acc->entriesPr[acc->cntEP] = initEntry();
				acc->entriesPr[acc->cntEP]->cnt[sale->month - 1] = 1;
				acc->entriesPr[acc->cntEP]->records[sale->month - 1][0] = acc->cntS;
				acc->entriesPr[acc->cntEP]->units += sale->amnt;
				*(int**)pr->data = malloc(sizeof(int));
				*(*(int**)pr->data) = acc->cntS;
				*pr->dataSize = sizeof(int);
				 /*copyEntry(&acc->entriesPr[i], acc->entriesPr[i]);*/
			}
			acc->cntEP++;

	/*Now bind the sale to the client*/
		
		/*Check if the client already has an entry bound by checking metadata*/
			if (*cl->dataSize != 0)
			{
				i = *(*(int **)cl->data); /*Index of entriecl where the client is bound*/

				tE = acc->entriesCli[i];

				/*Check if there is space to add Entry, else realloc*/
					if (acc->entriesCli[i]->cnt[sale->month - 1] == acc->entriesCli[i]->cntS[sale->month - 1])
					{
						acc->entriesCli[i]->cntS[sale->month - 1] += acc->entriesCli[i]->cntS[sale->month - 1];
						realloc(acc->entriesCli[i]->records[sale->month - 1], acc->entriesCli[i]->cntS[sale->month - 1]);
					}
					acc->entriesCli[i]->records[sale->month - 1][acc->entriesCli[i]->cnt[sale->month - 1]] = acc->cntS;
					acc->entriesCli[i]->units += sale->amnt;

					/*copyEntry(&acc->entriesCli[i], tE);*/
					}/*Else create new client Entry, update metadata*/else{
					acc->entriesCli[acc->cntEC] = initEntry();
					acc->entriesCli[acc->cntEC]->cnt[sale->month - 1] = 1;
					acc->entriesCli[acc->cntEC]->records[sale->month - 1][0] = acc->cntS;
					acc->entriesCli[acc->cntEC]->units += sale->amnt;
					*(int**)cl->data = malloc(sizeof(int));
					*(*(int**)cl->data) = acc->cntS;
					*cl->dataSize = sizeof(int);
					/*copyEntry(&acc->entriesCli[acc->cntEC], tE);*/
					}
		
			acc->cntEC++;

		acc->cntS++;
}
		



Entry *initEntry()
{
	Entry *e = malloc(sizeof(Entry));
	int i;
	e->records = malloc(sizeof(int*) * 12);
	for (i = 0; i < 12; i++)
	{
		e->cnt[i] = 0;
		e->cntS[i] = 1;
		e->records[i] = malloc(sizeof(int));
	}
	e->units = 0;
	return e;
}

int getSalesCount(Accounting *acc)
{
	return acc ? acc->sizeS : -1;
}