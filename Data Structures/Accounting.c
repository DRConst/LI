#include "Accounting.h"

typedef struct entry
{
	int cnt[12]/*Number of Index entries per Month (width of matrix at that row)*/, cntS[12];
	int units;
	int **records; /* Matrix Month x Index */
}Entry_s;


typedef struct accounting
{
	int cntEC, cntEP, sizeEC, sizeEP, sizeS, cntS;
	Entry_s **entriesCli, **entriesPr;
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
	s->product = malloc(sizeof(char)* 70);
	strcpy(s->product, product);
	s->client = malloc(sizeof(char)* 60);
	strcpy(s->client, client);
	s->data = malloc(sizeof(int*)* 10);
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
	return !( *dest == NULL );
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
int addSale(Accounting_s *acc, ClientCatalog *cCat, ProductCatalog *pCat, Sale *sale)
{
	/*Misc vars*/
	int i;

	/*Vars for reallocing*/
	Entry_s **reEC, **reEP;
	Sale **reS;

	/*Vars for product binding*/
	Product *pr;
	Entry_s *tE;
	Client *cl;

	/*Check if the sizes allow for insertion, if not realloc stuff*/

	if (acc->cntEC == acc->sizeEC)/*Client Entry_s array is full*/
	{
		if (!acc->sizeEC)
			acc->sizeEC = 2;
		else
			acc->sizeEC += acc->sizeEC;
		reEC = malloc(sizeof(Entry_s*)*acc->sizeEC);
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
		reEP = malloc(sizeof(Entry_s*)*acc->sizeEP);
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
		reS = malloc(sizeof(Entry_s*)*acc->sizeS);
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

	/*Next, add sale to the registry*/
	if( !copySale(&acc->sales[acc->cntS], sale) )
        return 0;

    /*Now bind the sale to the product*/
	/*Check if the product already has an entry bound by checking metadata*/
	if (*pr->dataSize != 0)
	{
		i = *(*(int **)pr->data); /*Index of entriePr where the product is bound*/

		tE = acc->entriesPr[i];

		/*Check if there is space to add Entry_s, else realloc*/
		if (acc->entriesPr[i]->cnt[sale->month - 1] == acc->entriesPr[i]->cntS[sale->month - 1])
		{
			acc->entriesPr[i]->cntS[sale->month - 1] += acc->entriesPr[i]->cntS[sale->month - 1];
			realloc(acc->entriesPr[i]->records[sale->month - 1], acc->entriesPr[i]->cntS[sale->month - 1]);
		}
		acc->entriesPr[i]->records[sale->month - 1][acc->entriesPr[i]->cnt[sale->month - 1]] = acc->cntS;
		bindData(acc->sales[acc->cntS], &acc->entriesPr[i]->records[sale->month - 1][acc->entriesPr[i]->cnt[sale->month - 1]]);
		acc->entriesPr[i]->units += sale->amnt;
/*        acc->entriesPr[i]->cnt[ (sale->month - 1) ] ++; */

		/*copyEntry(&acc->entriesPr[i], tE);*/
	}/*Else create new Product Entry_s, update metadata*/else{
		acc->entriesPr[acc->cntEP] = initEntry();
		acc->entriesPr[acc->cntEP]->cnt[sale->month - 1] = 1;
		acc->entriesPr[acc->cntEP]->records[sale->month - 1][0] = acc->cntS;
		acc->entriesPr[acc->cntEP]->units += sale->amnt;
		*(int**)pr->data = malloc(sizeof(int));
		*(*(int**)pr->data) = acc->cntS;
		*pr->dataSize = sizeof(int);
		bindData(acc->sales[acc->cntS], &acc->entriesPr[acc->cntEP]->records[sale->month - 1][0]);
		/*copyEntry(&acc->entriesPr[i], acc->entriesPr[i]);*/
	}
	acc->cntEP++;

	/*Now bind the sale to the client*/

	/*Check if the client already has an entry bound by checking metadata*/
	if (*cl->dataSize != 0)
	{
		i = *(*(int **)cl->data); /*Index of entriecl where the client is bound*/
printf("gotidx: %d", i);
		tE = acc->entriesCli[i];

		/*Check if there is space to add Entry_s, else realloc*/
		if (acc->entriesCli[i]->cnt[sale->month - 1] == acc->entriesCli[i]->cntS[sale->month - 1])
		{
			acc->entriesCli[i]->cntS[sale->month - 1] += acc->entriesCli[i]->cntS[sale->month - 1];
			realloc(acc->entriesCli[i]->records[sale->month - 1], acc->entriesCli[i]->cntS[sale->month - 1]);
		}
		acc->entriesCli[i]->records[sale->month - 1][acc->entriesCli[i]->cnt[sale->month - 1]] = acc->cntS;
		bindData(acc->sales[acc->cntS], &acc->entriesCli[i]->records[sale->month - 1][acc->entriesCli[i]->cnt[sale->month - 1]]);
		acc->entriesCli[i]->units += sale->amnt;
		printf("got here\n");
        acc->entriesCli[i]->cnt[ (sale->month - 1) ] ++;


        printf("c: %d\n", tE->cnt[ sale->month - 1 ] );
		/*copyEntry(&acc->entriesCli[i], tE);*/
	}/*Else create new client Entry_s, update metadata*/else{
		acc->entriesCli[acc->cntEC] = initEntry();
		acc->entriesCli[acc->cntEC]->cnt[sale->month - 1] = 1;
		acc->entriesCli[acc->cntEC]->records[sale->month - 1][0] = acc->cntS;
		acc->entriesCli[acc->cntEC]->units += sale->amnt;
		*(int**)cl->data = malloc(sizeof(int));
		*(*(int**)cl->data) = acc->cntS;
		*cl->dataSize = sizeof(int);

		bindData(acc->sales[acc->cntS], &acc->entriesCli[acc->cntEC]->records[sale->month - 1][0]);
		/*copyEntry(&acc->entriesCli[acc->cntEC], tE);*/
	}

	acc->cntEC++;

	acc->cntS++;

	return 1;
}


void quick_sort(int *a, int n) {
	int b, i, j;

	for ( i = 0; i < n; ++i)
	{
		for ( j = i + 1; j < n; ++j)
		{
			if (a[i] > a[j])
			{
				b = a[i];
				a[i] = a[j];
				a[j] = b;
			}
		}
	}
}


int orderAcc(Accounting_s *acc)
{

	int i;
	int *j = malloc(sizeof(int)*acc->cntEC);
	int *k = malloc(sizeof(int)*acc->cntEP);
	intBST *b = initBST(), *b1 = initBST(); int cnt = 0;
	Entry **cliE, **prE;
	Node *n;
	int *toRet;
	cliE = malloc(sizeof(Entry*)*acc->cntEC);
	prE = malloc(sizeof(Entry*)*acc->cntEP);
	/* memcpy(cliE, acc->entriesCli, sizeof(Entry*)*acc->cntEC); */

	for (i = 0; i < acc->cntEC; i++)
	{
	j[i] = i;
	if (!acc->entriesCli[i])
	i = i;
	else
	{
	insertBST(b, acc->entriesCli[i]->units, &j[i], sizeof(int));
	cnt++;
	}

	}
	toRet = inOrderBST(b);
	for (i = 0; i < b->used; i++)
	{

	int *a = malloc(sizeof(int));
	int c;
	getNodeData(getNode(b, toRet[i]), &a, &c);
	cliE[i] = acc->entriesCli[*a];
	}
	acc->entriesCli = cliE;
	acc->cntEC = b->used;
	freeBST(b);
	for (i = 0; i < acc->cntEP; i++)
	{
		k[i] = i;
		if (!acc->entriesPr[i])
			i = i;
		else
		{
			insertBST_it(b1, acc->entriesPr[i]->units, &k[i], sizeof(int));
			/*cnt++;*/
		}
	}
	toRet = inOrderBST_it(b1);

	cnt = 0;
	for (i = 0; i < b1->used; i++)
	{

		int *a = malloc(sizeof(int));
		int	c;
		getNodeData(getNode(b1, toRet[i]), &a, &c);
		prE[i] = acc->entriesPr[*a];
		cnt++;
	}
	acc->entriesPr = prE;
	acc->cntEP = b1->used;
	for (i = 0; i < acc->cntEP; i++)
	{
		printf("%d\n", acc->entriesPr[i]->units);
	}

	return 1;
}

Entry_s *initEntry()
{
	Entry_s *e = malloc(sizeof(Entry_s));
	int i;
	e->records = malloc(sizeof(int*)* 12);
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

int getEntriesClientsCount( Accounting_s *acc )
{
    return acc ? acc->cntEC : -1;
}

int getEntriesProductsCount( Accounting_s *acc )
{
    return acc ? acc->cntEP : -1;
}

int getProductSalesPerMonth( Accounting_s *acc, Product prod, int month, int *nSalesP, int *nSalesN, double *totalProfit )
{
    int i, idx;
    int count, countN, countP;
    double total;
    Entry *e;


    if( !(acc->cntEP) || !(*(prod.dataSize)) )
        return 0;

    idx = *(*(int **)prod.data);

    e = acc->entriesPr[ idx ];

    if( !e )
        return 0;

    month--;

    count = e->cnt[ month ];

    countN = countP = 0;
    total = 0.0;

    for( i = 0; i < count; i++) {
        if( acc->sales[ e->records[ month ][i] ]->type == 'N' )
            countN++;
        else
            countP++;
        total += acc->sales[ e->records[ month ][i] ]->price;
    }

    *nSalesN = countN;
    *nSalesP = countP;
    *totalProfit = total;

    return count;
}

char **getProductsNeverBought( Accounting *acc )
{
    char **toRet = NULL, buff[5];


}
