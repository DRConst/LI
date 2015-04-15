#include "Accounting.h"

typedef struct entry
{
	int cnt[12]/*Number of Index entries per Month (width of matrix at that row)*/, cntS[12];
	int units;
	int **records; /* Matrix Month x Index */
	char name[8];/*debug only*/
}*Entry_s;


struct montly_purchases
{
	char **list;
	int *cnt;
	int size;
};


typedef struct accounting
{
	int cntEC, cntEP, sizeEC, sizeEP, sizeS, cntS;
	Entry_s *entriesCli, *entriesPr;
	Sale **sales;
}Accounting_s;


Sale *createSale(int month, int amnt, double price, char *product, char *client, char type)
{
	Sale *s = malloc(sizeof(Sale));
	if (!s)
		return NULL;
	s->amnt = amnt;
	s->month = month;
	s->price = price;
	s->type = type;
	s->product = malloc(sizeof(char) * 70);
	strcpy(s->product, product);
	s->client = malloc(sizeof(char) * 60);
	strcpy(s->client, client);
	s->data = malloc(sizeof(int*) * 10);
	s->dataC = 1;
	s->dataS = 10;
	return s;
}


Accounting_s *initAccounting()
{
	Accounting_s *acc = malloc(sizeof(Accounting_s));
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

	/* return *(dest) == NULL; */
	return !(*dest == NULL);
	/*dest->amnt = src->amnt;
	strcpy(dest->client,src->client);
	strcpy(dest->product, src->product);
	dest->month = src->month;
	dest->price = src->price;
	dest->type = src->type;*/
}

void bindData(Sale *s, int *i)
{
	if (s->dataC == s->dataS)
	{
		s->dataS += s->dataS;
		s->data = realloc(s->data, s->dataS);
	}
	s->data[s->dataC++] = i;
}
int addSale(Accounting_s *acc, ClientCatalog cCat, ProductCatalog pCat, Sale *sale)
{
	/*Misc vars*/
	int i, monthIdx;

	/*Vars for reallocing*/
	Entry_s *reEC, *reEP;
	Sale **reS;

	/*Vars for product binding*/
	Product pr;
	Entry_s tE;
	Client cl;

	/*Check if the sizes allow for insertion, if not realloc stuff*/

	if (acc->cntEC == acc->sizeEC)/*Client Entry_s array is full*/
	{
		if (!acc->sizeEC)
			acc->sizeEC = 2;
		else
			acc->sizeEC += acc->sizeEC;

		/* TODO: CHANGE TO REALLOC */
		reEC = malloc(sizeof(*reEC)*acc->sizeEC);
		for (i = 0; i < acc->sizeEC / 2; i++)
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

	if (acc->cntEP == acc->sizeEP)/*Product Entry_s array is full*/
	{

		if (!acc->sizeEP)
			acc->sizeEP = 2;
		else
			acc->sizeEP += acc->sizeEP;
		reEP = malloc(sizeof(*reEP)*acc->sizeEP);
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
		reS = malloc(sizeof(*reS)*acc->sizeS);
		for (i = 0; i < acc->sizeS / 2; i++)
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



	/* First, get, if valid, Product/Client */
	pr = getProduct(pCat, sale->product);
	if (!pr)
		return 0;
	cl = getClient(cCat, sale->client);
	if (!cl)
		return 0;

	monthIdx = sale->month - 1;

	/*Next, add sale to the registry*/
	if (!copySale(&acc->sales[acc->cntS], sale))
		return 0;

	/*Now bind the sale to the product*/
	/*Check if the product already has an entry bound by checking metadata*/
	if (*pr->dataSize != 0)
	{
		i = *(*(int **)pr->data); /*Index of entriePr where the product is bound*/

		tE = acc->entriesPr[i];

		/*Check if there is space to add Entry_s, else realloc*/
		if (tE->cnt[monthIdx] == tE->cntS[monthIdx])
		{
			tE->cntS[monthIdx] *= 2;
			tE->records[monthIdx] = realloc(tE->records[monthIdx], sizeof(int)*tE->cntS[monthIdx]);
		}
		tE->records[monthIdx][tE->cnt[monthIdx]] = acc->cntS;
		bindData(acc->sales[acc->cntS], &tE->records[monthIdx][tE->cnt[monthIdx]]);
		tE->units += sale->amnt;
		tE->cnt[(monthIdx)] ++;

		/*copyEntry(&tE, tE);*/
	}/*Else create new Product Entry_s, update metadata*/else{
		acc->entriesPr[acc->cntEP] = initEntry();
		acc->entriesPr[acc->cntEP]->cnt[monthIdx] = 1;
		acc->entriesPr[acc->cntEP]->records[monthIdx][0] = acc->cntS;
		acc->entriesPr[acc->cntEP]->units += sale->amnt;
		*(int**)pr->data = malloc(sizeof(int));
		*(*(int**)pr->data) = acc->cntS;
		*pr->dataSize = sizeof(int);
		strcpy(acc->entriesPr[acc->cntEP]->name, pr->name);
		bindData(acc->sales[acc->cntS], &acc->entriesPr[acc->cntEP]->records[monthIdx][0]);
		/*copyEntry(&tE, tE);*/
	}
	acc->cntEP++;

	/*Now bind the sale to the client*/

	/*Check if the client already has an entry bound by checking metadata*/
	if (*cl->dataSize != 0)
	{
		i = *(*(int **)cl->data); /*Index of entriecl where the client is bound*/
		tE = acc->entriesCli[i];

		/*Check if there is space to add Entry_s, else realloc*/
		if (tE->cnt[monthIdx] == tE->cntS[monthIdx])
		{
			tE->cntS[monthIdx] *= 2;
			tE->records[monthIdx] = realloc(tE->records[monthIdx], sizeof(int)*tE->cntS[monthIdx]);
		}
		tE->records[monthIdx][tE->cnt[monthIdx]] = acc->cntS;
		bindData(acc->sales[acc->cntS], &tE->records[monthIdx][tE->cnt[monthIdx]]);
		tE->units += sale->amnt;
		tE->cnt[(monthIdx)] ++;


		/*copyEntry(&tE, tE);*/
	}/*Else create new client Entry_s, update metadata*/else{
		acc->entriesCli[acc->cntEC] = initEntry();
		acc->entriesCli[acc->cntEC]->cnt[monthIdx] = 1;
		acc->entriesCli[acc->cntEC]->records[monthIdx][0] = acc->cntS;
		acc->entriesCli[acc->cntEC]->units += sale->amnt;
		*(int**)cl->data = malloc(sizeof(int));
		*(*(int**)cl->data) = acc->cntS;
		*cl->dataSize = sizeof(int);
		strcpy(acc->entriesCli[acc->cntEC]->name, cl->name);
		bindData(acc->sales[acc->cntS], &acc->entriesCli[acc->cntEC]->records[monthIdx][0]);
		/*copyEntry(&acc->entriesCli[acc->cntEC], tE);*/
	}

	acc->cntEC++;

	acc->cntS++;

	return 1;
}



int orderAcc(Accounting_s *acc, ProductCatalog pCat, ClientCatalog cCat)
{
	minHeap h1 = newHeap(acc->cntEC), h2 = newHeap(acc->cntEC);
	int letter, i, tI = 0, metaI, lSize, hUsed, hSize;
	char **lists;
	Client cl; Product pr;
	Entry_s cliE, prE, *tCE, *tPE;
	Elem e;
	int cnt = 0;

	StringList sl;
	for (letter = 0; letter < 26; letter++)
	{
		sl = getClientsByPrefix(cCat, 'A' + letter);
		lSize = getCountStringList(sl);
		lists = getStringList(sl);
		for (i = 0; i < lSize; i++)
		{
			cl = getClient(cCat, lists[i]);
			if (!cl->data)
			{
				/*Client has no records*/
			}
			else
			{
				metaI = *(*(int**)cl->data);
				cliE = acc->entriesCli[metaI];
				insertHeap(h1, cliE->units, cliE, sizeof cliE);
			}
			/*free(lists[i]);*/
		}
		/*free(lists);*/
	}
	freeStringList(sl);
	for (letter = 0; letter < 26; letter++)
	{
		sl = getProductsByPrefix(pCat, 'A' + letter);
		lSize = getCountStringList(sl);
		lists = getStringList(sl);
		for (i = 0; i < lSize; i++)
		{
			pr = getProduct(pCat, lists[i]);
			if (!*pr->data)
			{
				/*Client has no records*/
			}
			else
			{
				metaI = *(*(int**)pr->data);
				prE = acc->entriesPr[metaI];
				insertHeap(h2, prE->units, prE, sizeof prE);
			}
			/*free(lists[i]);*/
		}
		/*free(lists);*/
	}
	freeStringList(sl);
	hUsed = getUsed(h1);
	acc->cntEC = hUsed;
	tCE = malloc(sizeof *tCE * acc->cntEC);
	hSize = getSize(h1);
	for (i = 0; i < hUsed; i++)
	{
		e = extractMin(h1);
		tCE[i] = (Entry_s)getElemDataAddr(e);
		cl = getClient(cCat, tCE[i]->name);
		*(*(int**)cl->data) = i;
	}
	acc->entriesCli = tCE;

	hUsed = getUsed(h2);
	acc->cntEP = hUsed;
	tPE = malloc(sizeof *tPE * acc->cntEP);
	hSize = getSize(h2);
	for (i = 0; i < hUsed; i++)
	{
		e = extractMin(h2);
		tPE[i] = (Entry_s)getElemDataAddr(e);
		pr = getProduct(pCat, tPE[i]->name);
		*(*(int**)pr->data) = i;
		pr = getProduct(pCat, tPE[i]->name);
		hSize = *(*(int**)pr->data);
		hSize = hSize;
	}
	acc->entriesPr = tPE;
}

Entry_s initEntry()
{
	Entry_s e = malloc(sizeof(*e));
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

int getSalesCount(Accounting_s *acc)
{
	return acc ? acc->cntS : -1;
}

int getEntriesClientsCount(Accounting_s *acc)
{
	return acc ? acc->cntEC : -1;
}

int getEntriesProductsCount(Accounting_s *acc)
{
	return acc ? acc->cntEP : -1;
}

int getProductSalesPerMonth(Accounting_s *acc, Product prod, int month, int *nSalesP, int *nSalesN, double *totalProfit)
{
	int i, idx;
	int count, countN, countP;
	double total;
	Entry *e;


	if (!(acc->cntEP) || !(prod->dataSize))
		return 0;

	idx = *(*(int **)prod->data);

	e = acc->entriesPr[idx];

	if (!e)
		return 0;

	month--;

	count = e->cnt[month];

	countN = countP = 0;
	total = 0.0;

	for (i = 0; i < count; i++)
	{
		if (acc->sales[e->records[month][i]]->type == 'N')
			countN++;
		else
			countP++;
		total += acc->sales[e->records[month][i]]->price;
	}

	*nSalesN = countN;
	*nSalesP = countP;
	*totalProfit = total;

	return count;
}


ProductBuyers productBuyers(Accounting acc, ProductCatalog pCat, ClientCatalog cCat, char *product)
{
	ProductBuyers toRet = malloc(sizeof *toRet);
	ClientCatalog tmpP = initClientCatalog();
	ClientCatalog tmpN = initClientCatalog();
	Product pr = getProduct(pCat, product);
	int index = getProductMetaData(pr);
	int i = 0, j, l;
	Entry_s p = acc->entriesPr[index];
	Sale *s;

	toRet->cntN = 0; toRet->cntP = 0; toRet->listN = NULL; toRet->listP = NULL;
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < p->cnt[i]; j++)
		{
			s = acc->sales[p->records[i][j]];
			if (s->type == 'N')
			{
				if (!existsClient(tmpN, s->client))
				{
					insertClient(tmpN, s->client);
					toRet->listN = realloc(toRet->listN, sizeof(char*) * toRet->cntN + 1);
					toRet->listN[toRet->cntN] = malloc(sizeof(char) * 6);
					strcpy(toRet->listN[toRet->cntN++], s->client);
				}
			}
			if (s->type == 'P')
			{
				if (!existsClient(tmpP, s->client))
				{
					insertClient(tmpP, s->client);
					toRet->listP = realloc(toRet->listP, sizeof(char*) * toRet->cntP + 1);
					toRet->listP[toRet->cntP] = malloc(sizeof(char) * 6);
					strcpy(toRet->listP[toRet->cntP++], s->client);
				}
			}
		}
	}
	return toRet;
}

Monthly_Purchases mostBoughtMonthlyProductsByClient(Accounting acc, ProductCatalog pCat, ClientCatalog cCat, char *client, int month)
{
	StringList sl = initStringList;
	ProductCatalog tmp = initProductCatalog();	Product pr;
	Client cl = getClient(cCat, client);
	Entry_s e;
	intBST *b = initBST();
	Sale *s;
	minHeap h;
	int i, j, letter, lSize, cnt = 0, used, *tmpMP;
	Elem el;
	char **lists;
	Monthly_Purchases mp = initMonthlyPurchases();



	if (!cl)
		return NULL;
	int metaI = *(*(int**)cl->data);
	e = acc->entriesCli[metaI];
	if (!e)
		return NULL;
	h = newHeap(acc->cntEP);
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < e->cnt[i]; j++)
		{
			s = acc->sales[e->records[i][j]];
			if (existsProduct(tmp, s->product))
			{
				pr = getProduct(tmp, s->product);
				letter = *(*(int**)pr->data);
				*(*(int**)pr->data) = letter + 1;
			}
			else
			{
				insertProduct(tmp, s->product);
				pr = getProduct(tmp, s->product);
				*(int **)pr->data = malloc(sizeof(int));
				*(*(int **)pr->data) = 1;
				pr = getProduct(tmp, s->product);
				letter = *(*(int**)pr->data);
				cnt++;
			}
		}
	}

	for (letter = 0; letter < 26; letter++)
	{
		sl = getProductsByPrefix(tmp, 'A' + letter);
		lSize = getCountStringList(sl);
		lists = getStringList(sl);
		for (i = 0; i < lSize; i++)
		{
			pr = getProduct(tmp, lists[i]);
			if (!*pr->data)
			{
				/*Client has no records*/
			}
			else
			{
				j = *(*(int **)pr->data);
				insertHeap(h, *(*(int **)pr->data), pr->name, sizeof(char) * 6);
			}
			/*free(lists[i]);*/
		}
		/*free(lists);*/
	}
	freeStringList(sl);
	sl = initStringList();
	used = getUsed(h);
	lists = malloc(sizeof(char*)*used);
	tmpMP = malloc(sizeof(int)*used);
	cnt = 0;
	for (i = 0; i < used; i++)
	{
		el = extractMin(h);
		lists[cnt] = getElemDataAddr(el);
		tmpMP[cnt++] = getElemKey(el);
	}
	for (i = cnt - 1; i > 0; i--)
	{
		registerMonthlyPurchase(mp, lists[i],tmpMP[i]);
		printf("%s: %d\n", mp->list[mp->size - 1], mp->cnt[mp->size - 1]);
	}
	return mp;

}

StringList yearRoundClients(Accounting acc, ProductCatalog pCat, ClientCatalog cCat)
{
	StringList toRet = initStringList();
	int i = acc->cntEC - 1, j,k;
	Entry_s ent = acc->entriesCli[i--];
	while (ent && ent->units > 12 &&  i > 0)
	{
		k = 1;
		for (j = 0; j < 12 && k; j++)
		{
			if (ent->cnt[j] < 1)
				k = 0;
		}
		if (k)
			insertStringList(toRet, ent->name, sizeof ent->name);
		ent = acc->entriesCli[i--];
	}
	return toRet;
}

StringList mostSoldProducts(Accounting acc, ProductCatalog pCat, ClientCatalog cCat, int N)
{
	StringList sl = initStringList();
	int i = acc->cntEP - 1,j,k;
	int cli = 0;
	Entry_s ent;
	ClientCatalog tmp = initClientCatalog();
	Sale *s;
	char *buff = calloc(50, sizeof (char));
	char b[10];
	for (i, N; i > 0 && N > 0; i--, N--)
	{
		ent = acc->entriesPr[i];
		for (j = 0; j < 12; j++)
			for (k = 0; k < ent->cnt[j]; k++)
			{
				s = acc->sales[ent->records[j][k]];
				if (!existsClient(tmp, s->client))
				{
					insertClient(tmp, s->client);
					cli++;
				}
			}
		memset(buff, '\0', 50);
		strcat(buff, ent->name);
		strcat(buff, " for ");
		itoa(cli, b, 10);
		strcat(buff, b);
		strcat(buff, " clients and ");
		itoa(ent->units, b, 10);
		strcat(buff, b);
		strcat(buff, " units\n");
		insertStringList(sl, buff, 50);
		cli = 0;
	}
	return sl;
}


StringList productsWithoutPurchases(Accounting acc)
{
	int i;
	StringList sl = initStringList();
	for (i = 0; i < acc->cntEP && acc->entriesPr[i]->units == 0; i++)
	{
		insertStringList(sl, acc->entriesPr[i]->name, 7);
	}
	return sl;

}

StringList clientsWithoutPurchases(Accounting acc)
{
	int i;
	StringList sl = initStringList();
	for (i = 0; i < acc->cntEC && acc->entriesCli[i]->units == 0; i++)
	{
		insertStringList(sl, acc->entriesCli[i]->name, 6);
	}
	return sl;

}
/*MONTHLY PURCHASES FUNCTIONS*/

Monthly_Purchases initMonthlyPurchases()
{
	Monthly_Purchases toRet = malloc(sizeof *toRet);
	toRet->cnt = NULL;
	toRet->list = NULL;
	toRet->size = 0;
	return toRet;
}

Monthly_Purchases registerMonthlyPurchase(Monthly_Purchases mp, char *product, int cnt)
{
	mp->list = realloc(mp->list, sizeof(char*) * mp->size + 1);
	mp->list[mp->size] = malloc(sizeof(char) * 6);
	strcpy(mp->list[mp->size], product);
	mp->cnt = realloc(mp->cnt, sizeof(int) * mp->size + 1);
	mp->cnt[mp->size++] = cnt;
	return mp;
}

char **getMonthlyPurchasesList(Monthly_Purchases mp)
{
	return mp->list;
}
int *getMonthlyPurchasesCounts(Monthly_Purchases mp)
{
	return mp->cnt;
}
int getMonthlyPurchasesSize(Monthly_Purchases mp)
{
	return mp->size;
}
/*END MONTHLY PURCHASES FUNCTIONS*/