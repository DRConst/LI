#include "Accounting.h"

typedef struct entryAcc
{
    int cntSalesP[13];  /* Month Array, idx0 is total */
    int cntSalesN[13];  /* Month Array, idx0 is total */
    double profit[13];  /* Month Array, idx0 is total */
    int units[13];
	char name[8];/*debug only*/
}*EntryAcc;


typedef struct accounting
{
	int cntEC, cntEP, sizeEC, sizeEP;
	EntryAcc *entriesCli, *entriesPr;
}*Accounting_s;

typedef struct csv_stats
{
	StringList sl1, sl2;
}*csv_Stats_s;

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
		tE = acc->entriesPr[i];

    else { /*Else create new Product Entry_s, update metadata*/

        setProductMetaData(pr, acc->cntEP, "Accounting");
        setProductDataSize(pr,sizeof(int));

        i = acc->cntEP;

	    tE = acc->entriesPr[ i ] = initEntryAcc();

	    strcpy(tE->name, getProductName(pr));



		/*copyEntry(&tE, tE);*/
		acc->cntEP++;
	}

    if( getSaleType( sale ) == 'P' ) {
        tE->cntSalesP[ monthIdx ]++;
        tE->cntSalesP[ 0 ]++;
    }else {
        tE->cntSalesN[ 0 ]++;
        tE->cntSalesN[ monthIdx ]++;
    }

    tE->units[ 0 ] += getSaleQtd( sale );
    tE->units[ monthIdx ] += getSaleQtd( sale );

    tE->profit[ 0 ] += getSalePrice( sale ) * getSaleQtd( sale );
    tE->profit[ monthIdx ] += getSalePrice( sale ) * getSaleQtd( sale );

	if ((clientHasMetaData(cl, "Accounting") != 0) && acc->entriesCli[(i = getClientMetaData(cl, "Accounting"))] != NULL)
		tE = acc->entriesCli[i];

    else { /*Else create new Client EntryAcc, update metadata*/

        setClientMetaData(cl,acc->cntEC, "Accounting");
        setClientDataSize(cl,sizeof(int));

        i = acc->cntEC;

	    tE = acc->entriesCli[ i ] = initEntryAcc();

	    strcpy(tE->name, getClientName(cl));


		/*copyEntry(&tE, tE);*/
		acc->cntEC++;
	}

    if( getSaleType( sale ) == 'P' ) {
        tE->cntSalesP[ monthIdx ]++;
        tE->cntSalesP[ 0 ]++;
    }else {
        tE->cntSalesN[ 0 ]++;
        tE->cntSalesN[ monthIdx ]++;
    }

    tE->units[ 0 ] += getSaleQtd( sale );
    tE->units[ monthIdx ] += getSaleQtd( sale );

    tE->profit[ 0 ] += getSalePrice( sale ) * getSaleQtd( sale );
    tE->profit[ monthIdx ] += getSalePrice( sale ) * getSaleQtd( sale );


    return acc;
}

Accounting_s orderAcc(Accounting_s acc, ProductCatalog pCat, ClientCatalog cCat)
{
	minHeap h1 = newHeap( getClientCount(cCat) ), h2 = newHeap( getProductCount( pCat ) );
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
		freeStringList( sl );
	}

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
		freeStringList( sl );
	}
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

csv_Stats_s getMonthsStats(Accounting_s acc)
{
	int  i, j;
	int cntCli[12], cntRecords[12], k;
	csv_Stats_s toRet = malloc(sizeof(*toRet));
	StringList sl1 = initStringList(), sl2 = initStringList();
	char buff[64];
	for (i = 0; i < 12; i++)
	{
		cntCli[i] = 0;
		cntRecords[i] = 0;
	}
	for (i = 0; i < acc->cntEC; i++)
	{
		for (j = 0; j < 12; j++)
		{
			k = acc->entriesCli[i]->cntSalesN[j+1] + acc->entriesCli[i]->cntSalesP[j+1];
			if (k)
			{
				cntRecords[j] += k;
				cntCli[j]++;
			}
		}
	}
	for (i = 0; i < 12; i++)
	{
		sprintf(buff, "%d", cntCli[i]);
		sl1 = insertStringList(sl1, buff, sizeof buff);
		sprintf(buff, "%d", cntRecords[i]);
		sl2 = insertStringList(sl2, buff, sizeof buff);		
	}
	toRet->sl1 = sl1;
	toRet->sl2 = sl2;

	return toRet;
}

char **getList1CsvStats(csv_Stats_s s)
{
	return getStringList(s->sl1);
}
char **getList2CsvStats(csv_Stats_s s)
{
	return getStringList(s->sl2);
}
int getCntCsvStats(csv_Stats_s s)
{
	return getCountStringList(s->sl1);
}

int getMonthSalesPByProduct( Accounting_s acc, Product pr, int month )
{

    if( !acc )
        return -1;

    return acc->entriesPr[ getProductMetaData( pr, "Accounting" ) ]->cntSalesP[ month ];
}

int getTotalSalesPByProduct( Accounting_s acc, Product pr )
{

    if( !acc )
        return -1;

    return acc->entriesPr[ getProductMetaData( pr, "Accounting" ) ]->cntSalesP[ 0 ];
}

int getMonthSalesPByClient( Accounting_s acc, Client cl, int month )
{

    if( !acc )
        return -1;

    return acc->entriesCli[ getClientMetaData( cl, "Accounting" ) ]->cntSalesP[ month ];
}


int getTotalSalesPByClient( Accounting_s acc, Client cl )
{

    if( !acc )
        return -1;

    return acc->entriesCli[ getClientMetaData( cl, "Accounting" ) ]->cntSalesP[ 0 ];
}


double getMonthProfitByProduct( Accounting_s acc, Product pr, int month )
{
    if( !acc )
        return (double)-1;

    return acc->entriesPr[ getProductMetaData( pr, "Accounting" ) ]->profit[ month ];
}


double getTotalProfitByProduct( Accounting_s acc, Product pr )
{
    if( !acc )
        return (double)-1;

    return acc->entriesPr[ getProductMetaData( pr, "Accounting" ) ]->profit[ 0 ];
}


double getMonthProfitByClient( Accounting_s acc, Client cl, int month )
{
    if( !acc )
        return (double)-1;

    return acc->entriesCli[ getClientMetaData( cl, "Accounting" ) ]->profit[ month ];
}


double getTotalProfitByClient( Accounting_s acc, Client cl )
{
    if( !acc )
        return (double)-1;

    return acc->entriesCli[ getClientMetaData( cl, "Accounting" ) ]->profit[ 0 ];
}


int getTotalSalesNByProduct( Accounting_s acc, Product pr )
{

    if( !acc )
        return -1;

    return acc->entriesPr[ getProductMetaData( pr, "Accounting" ) ]->cntSalesN[ 0 ];
}

int getMonthSalesNByProduct( Accounting_s acc, Product pr, int month )
{

    if( !acc )
        return -1;

    return acc->entriesPr[ getProductMetaData( pr, "Accounting" ) ]->cntSalesN[ month ];
}

int getMonthSalesNByClient( Accounting_s acc, Client cl, int month )
{

    if( !acc )
        return -1;

    return acc->entriesCli[ getClientMetaData( cl, "Accounting" ) ]->cntSalesN[ month ];
}

int getTotalSalesNByClient( Accounting_s acc, Client cl )
{

    if( !acc )
        return -1;

    return acc->entriesCli[ getClientMetaData( cl, "Accounting" ) ]->cntSalesN[ 0 ];
}


int getMonthUnitsByProduct( Accounting_s acc, Product pr, int month )
{
    if( !acc )
        return -1;

    return acc->entriesPr[ getProductMetaData( pr, "Accounting") ]->units[ month ];
}

int getTotalUnitsByProduct( Accounting_s acc, Product pr )
{
    if( !acc )
        return -1;

    return acc->entriesPr[ getProductMetaData( pr, "Accounting" ) ]->units[ 0 ];
}

int getMonthUnitsByClient( Accounting_s acc, Client cl, int month )
{
    if( !acc )
        return -1;

    return acc->entriesCli[ getClientMetaData( cl, "Accounting" ) ]->units[ month ];
}

int getTotalUnitsByClient( Accounting_s acc, Client cl )
{
    if( !acc )
        return -1;

    return acc->entriesCli[ getClientMetaData( cl, "Accounting" ) ]->units[ 0 ];
}

int getAccountingCount( Accounting_s acc )
{

    if( !acc )
        return 0;

    return ( acc->cntEC + acc->cntEP );
}

StringList getAccountingUnboughtProducts( Accounting_s acc )
{
    StringList sl = initStringList();
    int i;
    EntryAcc tE;


    i = acc->cntEP;
/*
    for( tE = acc->entriesPr[ i = acc->cntEP - 1 ];
        i && ( tE->cntSalesN[0] + tE->cntSalesP[0]  ) ;
    tE = acc->entriesPr[i], i-- )
        insertStringList( sl, tE->name, 7 );
*/

    for( i = 0; i < acc->cntEP; i++ ) {
        tE = acc->entriesPr[i];
        if( !( tE->cntSalesN[0] + tE->cntSalesP[0] ) )
            insertStringList( sl, tE->name, 7 );
    }

    return sl;
}
