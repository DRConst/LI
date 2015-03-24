#include "Accounting.h"


Sale *createSale(int month, int amnt, double price, char *product, char *client, char type)
{
	Sale *s = malloc(sizeof(Sale));
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
	Entry *cliE, *cliP;
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
	if (pr->data != NULL && *pr->data != NULL)
	{

	}

	cliE = initEntry();
	cliP = initEntry();

	
	

	acc->cntS++;
}



Entry *initEntry()
{
	Entry *e = malloc(sizeof(Entry));
	e->cnt = NULL;
	e->cntS = 0;
	e->units = 0;
	e->records = NULL;
	return e;
}