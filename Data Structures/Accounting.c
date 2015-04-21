#include "Accounting.h"

typedef struct entryAcc
{
    int cntSalesP[13];  /* Month Array, idx0 is total */
    int cntSalesN[13];  /* Month Array, idx0 is total */
    double profit[13];  /* Month Array, idx0 is total */
	char name[8];/*debug only*/
}*EntryAcc;


typedef struct accounting
{
	int cntEC, cntEP, sizeEC, sizeEP;
	EntryAcc *entriesCli, *entriesPr;
}*Accounting_s;


EntryAcc initEntryAcc()
{
	EntryAcc e = malloc(sizeof(*e));
	int i;


	for (i = 0; i < 13; i++)
	{
	    e->cntSalesN[i] = 0;
	    e->cntSalesP[i] = 0;
	    e->profit[i] = (double)0;
	}

	strcpy( e->name, "" );


	return e;
}


Accounting_s initAccounting()
{
	Accounting_s acc = malloc(sizeof(*acc));

	acc->cntEC = 0;
	acc->cntEP = 0;
	acc->sizeEC = 0;
	acc->sizeEP = 0;
	acc->entriesCli = NULL;
	acc->entriesPr = NULL;

	return acc;
}

Accounting_s addAccounting( Accounting_s acc, ClientCatalog cCat, ProductCatalog pCat,  Sale sale )
{
    int i = -1;

    Product pr = NULL;
    Client cl = NULL;

    EntryAcc tE = NULL;

    int monthIdx;




	/*Check if the sizes allow for insertion, if not realloc stuff*/

	if (acc->cntEC == acc->sizeEC)/*Client EntryAcc array is full*/
	{
		if (!acc->sizeEC)
			acc->sizeEC = 1;
		else
			acc->sizeEC += acc->sizeEC;

        acc->entriesCli = realloc( acc->entriesCli,
                            ( sizeof( struct entryAcc ) * acc->sizeEC ) );

		for (i = acc->sizeEC / 2; i < acc->sizeEC; i++)
			acc->entriesCli[i] = NULL;

	}

	if (acc->cntEP == acc->sizeEP)/*Product EntryAcc array is full*/
	{

		if (!acc->sizeEP)
			acc->sizeEP = 1;
		else
			acc->sizeEP += acc->sizeEP;

        acc->entriesPr = realloc( acc->entriesPr,
                            ( sizeof( struct entryAcc ) * acc->sizeEP ) );

		for (i = acc->sizeEP / 2; i < acc->sizeEP; i++)
			acc->entriesPr[i] = NULL;

	}



	/* First, get, if valid, Product/Client */
	if( matchProductPattern( getSaleProduct( sale ) ) )
        pr = getProduct(pCat, getSaleProduct( sale ) );
	if (!pr)
		return acc;

    if( matchClientPattern( getSaleClient( sale ) ) )
        cl = getClient(cCat, getSaleClient( sale ) );
	if (!cl)
		return acc;

	monthIdx = getSaleMonth( sale );


	/*Now bind the sale to the product*/
	/*Check if the product already has an entry bound by checking metadata*/
	if ((productHasMetaData(pr, "Accounting") != 0) && (acc->entriesPr[(i = getProductMetaData(pr, "Accounting"))] != NULL))
	{

		tE = acc->entriesPr[i];

        if( getSaleType( sale ) == 'P' ) {
            tE->cntSalesP[ monthIdx ]++;
            tE->cntSalesP[ 0 ]++;
        }else {
            tE->cntSalesN[ 0 ]++;
            tE->cntSalesN[ monthIdx ]++;
        }

        tE->profit[ 0 ] += getSalePrice( sale );
        tE->profit[ monthIdx ] += getSalePrice( sale );

		/*copyEntry(&tE, tE);*/
	}/*Else create new Product Entry_s, update metadata*/else{

        setProductMetaData(pr, acc->cntEP, "Accounting");
        setProductDataSize(pr,sizeof(int));

        i = acc->cntEP;

	    tE = acc->entriesPr[ i ] = initEntryAcc();

	    strcpy(tE->name, getProductName(pr));



		/*copyEntry(&tE, tE);*/
		acc->cntEP++;
	}

	if ((clientHasMetaData(cl, "Accounting") != 0) && acc->entriesCli[(i = getClientMetaData(cl, "Accounting"))] != NULL)
	{
		i = getClientMetaData(cl, "Accounting"); /*Index of entrieCl where the client is bound*/

		tE = acc->entriesCli[i];

        if( getSaleType( sale ) == 'P' ) {
            tE->cntSalesP[ monthIdx ]++;
            tE->cntSalesP[ 0 ]++;
        }else {
            tE->cntSalesN[ 0 ]++;
            tE->cntSalesN[ monthIdx ]++;
        }

        tE->profit[ 0 ] += getSalePrice( sale );
        tE->profit[ monthIdx ] += getSalePrice( sale );

		/*copyEntry(&tE, tE);*/
	}/*Else create new Product Entry_s, update metadata*/else{

        setClientMetaData(cl,acc->cntEC, "Accounting");
        setClientDataSize(cl,sizeof(int));

        i = acc->cntEC;

	    tE = acc->entriesCli[ i ] = initEntryAcc();

	    strcpy(tE->name, getClientName(cl));



		/*copyEntry(&tE, tE);*/
		acc->cntEC++;
	}

    return acc;
}

Accounting_s orderAcc(Accounting_s acc, ProductCatalog pCat, ClientCatalog cCat)
{
	minHeap h1 = newHeap(acc->cntEC), h2 = newHeap(acc->cntEP);
	int letter, i, metaI, lSize, hUsed;
	char **lists;
	Client cl; Product pr;
	EntryAcc cliE, prE, *tCE, *tPE;
	Elem e;

	StringList sl;
	for (letter = 0; letter < 26; letter++)
	{
		sl = getClientsByPrefix(cCat, 'A' + letter);
		lSize = getCountStringList(sl);
		lists = getStringList(sl);
		for (i = 0; i < lSize; i++)
		{
			cl = getClient(cCat, lists[i]);
			if (!clientHasMetaData(cl, "Accounting"))
			{
				/*Client has no records*/
				cliE = initEntryAcc();
				strcpy( cliE->name, getClientName( cl ) );
			}
			else
			{
				metaI = getClientMetaData(cl, "Accounting");
				cliE = acc->entriesCli[metaI];
			}

			insertHeap(h1,( cliE->cntSalesN[0] + cliE->cntSalesP[0] ), cliE, sizeof cliE);
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
			if (!productHasMetaData(pr, "Accounting"))
			{
				/*Client has no records*/
				prE = initEntryAcc();
				strcpy( prE->name, getProductName( pr ) );
			}
			else
			{
				metaI = getProductMetaData(pr, "Accounting");
				prE = acc->entriesPr[metaI];
			}

			insertHeap(h2, ( prE->cntSalesN[0] + prE->cntSalesP[0] ), prE, sizeof prE);
			/*free(lists[i]);*/
		}
		/*free(lists);*/
	}
	freeStringList(sl);
	hUsed = getUsed(h1);
	acc->cntEC = hUsed;
	tCE = malloc(sizeof *tCE * acc->cntEC);
	for (i = 0; i < hUsed; i++)
	{
		e = extractMin(h1);
		tCE[i] = (EntryAcc)getElemDataAddr(e);
		cl = getClient(cCat, tCE[i]->name);
		setClientMetaData(cl, i, "Accounting");
	}
	acc->entriesCli = tCE;

	hUsed = getUsed(h2);
	acc->cntEP = hUsed;
	tPE = malloc(sizeof *tPE * acc->cntEP);
	for (i = 0; i < hUsed; i++)
	{
		e = extractMin(h2);
		tPE[i] = (EntryAcc)getElemDataAddr(e);
		pr = getProduct(pCat, tPE[i]->name);
		setProductMetaData(pr, i, "Accounting");
	}
	acc->entriesPr = tPE;
	return acc;
}

int getTotalSalesPByProduct( Accounting_s acc, Product pr )
{
    int salesP;
    EntryAcc tE;
    int i;


    if( !acc )
        return 0;

    tE = acc->entriesPr[ getProductMetaData( pr, "Accounting" ) ];

    printf("name: %s", tE->name );

    for( i = 0; i < 13; i++ )
        printf("\n for month %d : salesP: %d, salesN: %d, money: %.2f", i, tE->cntSalesP[i], tE->cntSalesN[i], tE->profit[i] );

    return salesP;
}

int getAccountingCount( Accounting_s acc )
{

    if( !acc )
        return 0;

    return ( acc->cntEC + acc->cntEP );
}
