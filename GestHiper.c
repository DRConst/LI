#include "GestHiper.h"
void printMenu();

void readFiles( ProductCatalog prodCat, ClientCatalog clientCat, Sales sales, Accounting acc );
void ProductsByPrefix( ProductCatalog prodCat );
void ClientsByPrefix( ClientCatalog clientCat );
void getProductSalesInfo( ProductCatalog prodCat, Accounting acc );
void getUnboughtProducts( Accounting acc );
void getClientSalesCount( Sales sales, ClientCatalog clientCat );
void getSalesInterval( Accounting acc );
void getProductBuyers(Sales sales, ProductCatalog pCat );
void getClientSales(Sales sales, ProductCatalog pCat, ClientCatalog cCat);
void getActiveClients( Sales sales );
void generateCSV( Accounting acc );
void getMostWantedProducts(Sales sales );
void getClientMostWantedProducts( Sales sales, ClientCatalog cCat );
void getAllInactive( Sales sales );

int listsToCSV( char *fileName, int nLists, int listSize, ... );

void paginateResults( int nLists, int showIdx, int nPostArgs, ... );
void genColumn( char *ret, char *s, int max );
void parseRunTime( char *buff, float milis );
void freeData( ProductCatalog prodCat, ClientCatalog clientCat, Sales sales, Accounting acc );


int main()
{
	int op = 1;
    ProductCatalog prodCat = initProductCatalog();
    ClientCatalog clientCat = initClientCatalog();
    Sales sales = initSales();
	Accounting acc = initAccounting();
    int ret;




	do {
        fflush( stdin );
		printMenu();
		ret = scanf("%d", &op );

		fflush(stdin);

        #if _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        if( ret ) {
            switch( op ) {
                case 1:
					freeData(prodCat, clientCat, sales, acc);

					prodCat = initProductCatalog();

					clientCat = initClientCatalog();

					sales = initSales();

					acc = initAccounting();

                    readFiles( prodCat, clientCat, sales, acc );
                break;

                case 2:
                    ProductsByPrefix( prodCat );
                break;

                case 3:
                    getProductSalesInfo( prodCat, acc );
                break;

                case 4:
                    getUnboughtProducts( acc );
                break;

                case 5:
                    getClientSalesCount( sales, clientCat );
                break;

                case 6:
                    ClientsByPrefix( clientCat );
                break;

                case 7:
                    getSalesInterval( acc );
                break;

                case 8:
					getProductBuyers(sales, prodCat );
                break;

                case 9:
					getClientSales(sales, prodCat, clientCat);
                break;

                case 10:
					getActiveClients(sales );
                break;

                case 11:
                    generateCSV( acc );
                break;

                case 12:
                    getMostWantedProducts( sales );
                break;

                case 13:
                    getClientMostWantedProducts( sales , clientCat);
                break;

                case 14:
                    getAllInactive( sales );
                break;

                case 0:
                break;
            }
        }

	}while( op != 0 && op != EOF );


	return 0;
}

void printMenu()
{

	printf( HEADER_MENU
        MENU_OPTION_1
        MENU_OPTION_2
        MENU_OPTION_3
        MENU_OPTION_4
        MENU_OPTION_5
        MENU_OPTION_6
        MENU_OPTION_7
        MENU_OPTION_8
        MENU_OPTION_9
        MENU_OPTION_10
        MENU_OPTION_11
        MENU_OPTION_12
        MENU_OPTION_13
        MENU_OPTION_14
        EXIT_OPTION
        "\n	Option: "
    );
}



/* Query 1 */
void readFiles( ProductCatalog prodCat, ClientCatalog clientCat, Sales sales, Accounting acc )
{
	char clients[MAX_PATH] = "";
	char products[MAX_PATH] = "";
	char salesFile[MAX_PATH] = "";
	FILE *clientsFp, *productsFp, *salesFp;

    char type;
    int qtd, month, ret;
    char prod[7], client[6], buff[128];
    double price;
    Sale sale;

    clock_t tStart;
    char timeS[20] = "";

	printf("\n Optional file paths[Max: %d], enter for default\n", MAX_PATH);

	printf("\n Clients File: ");
	fgets( clients, MAX_PATH, stdin);

	printf("\n Products File: ");
	fgets( products, MAX_PATH, stdin);

	printf("\n Sales File: ");
	fgets( salesFile, MAX_PATH, stdin);

    /*  Time Start */
    tStart = clock();


	strtok( clients, "\n" );
	strtok( products, "\n" );
	strtok( salesFile, "\n" );

    if( strlen( products ) == 1 )
        strcpy( products, "FichProdutos.txt" );

    if( ( productsFp = fopen( products, "r" ) ) == NULL ) {
        printf( "\nProducts File Not Found");
        return;
    }


    if( strlen( clients ) == 1 )
        strcpy( clients, "FichClientes.txt" );

    if( ( clientsFp = fopen( clients, "r" ) ) == NULL ) {
        printf( "\nClients File Not Found");
        return;
    }


    if( strlen( salesFile ) == 1 )
        strcpy( salesFile, "Compras.txt" );

    if( ( salesFp = fopen( salesFile, "r" ) ) == NULL ) {
        printf( "\nSales File Not Found");
        return;
    }


    printf("\nReading Products Catalog...");
    while( fgets(buff, 8, productsFp ) )
    {
        if( matchProductPattern( buff ) )

            prodCat = insertProduct( prodCat, buff);
    }
    printf("Done \n\t%d read", getProductCount( prodCat ) );

    printf("\nReading Clients Catalog...");
    while( fgets(buff, 7, clientsFp ) )
    {
        if( matchClientPattern( buff ) )

            clientCat = insertClient( clientCat, buff);
    }
    printf("Done \n\t%d read", getClientCount( clientCat ) );

    printf("\nReading Sales Catalog...");
    while( fgets( buff, 64, salesFp ) )
    {
        ret = sscanf( buff, "%s %lf %d %c %s %d", prod, &price, &qtd, &type, client, &month );

        sale = createSale( month, qtd, price, prod, client, type );

        if( ret == 6 ) {
            sales = addSale( sales, clientCat, prodCat,
                    sale
            );
            acc = addAccounting( acc, clientCat, prodCat, sale );
        }
		freeSale(sale);
    }
    printf("Done \n\t%d read", getSalesCount( sales ) );

    printf("\nOrdering Sales Catalog...");
	sales = orderSales(sales, prodCat, clientCat);
    printf("Done");

    printf("\nOrdering Accounting Catalog...");
    acc = orderAcc( acc, prodCat, clientCat );
    printf("Done \n");

    /* Time End */
    parseRunTime( timeS, ( ( (float)clock() - (float)tStart ) / CLOCKS_PER_SEC ) * 1000 );

    printf("\nReading Finished in %s", timeS );

    getchar();

}

/* Query 2 */
void ProductsByPrefix( ProductCatalog prodCat )
{
	char c;
	StringList l;
	clock_t tStart;
	char timeS[20] = "";


	fflush( stdin );

	if( !getProductCount( prodCat ) ) {
        printf("\nProducts Catalog Not Initialized.");
        return;
	}

	printf("\n Enter Product Prefix[A-Z]: ");
	scanf( "%c", &c);

	c = toupper( c );


	if( c >= 'A' && c <= 'Z' ) {

        /* Time Start */
        tStart = clock();

        l = getProductsByPrefix( prodCat, c );

        /* Time End */
        parseRunTime( timeS, ( ( (float)clock() - (float)tStart ) / CLOCKS_PER_SEC ) * 1000 );

        if( getCountStringList( l ) )
            paginateResults( 1, 1, 1, 8, getStringList( l ), "Produtos", getCountStringList( l ), timeS );
        else
            printf( "\nNo Products By That Prefix" );

        freeStringList( l );

	}else
		printf("\nInvalid Input");

}

/* Query 3 */
void getProductSalesInfo( ProductCatalog prodCat, Accounting acc )
{
    int nMonth = 0;
    char prod[7] = "";
    Product pr;
    int ret;
    int nSalesP, nSalesN, count;
    double total;

    clock_t tStart;
    char timeS[20] = "";


	if( !getProductCount( prodCat ) ) {
        printf("\nProducts Catalog Not Initialized.");
        return;
	}

    if( !getAccountingCount( acc ) ) {
        printf("\nAccounting Structure Not Initialized.");
        return;
	}

	fflush( stdin );

    printf("\n Enter Product Code: ");
    fgets( prod, 7, stdin );

    fflush( stdin );

    printf("\n Enter Month[1,12]: ");
    ret = scanf("%d", &nMonth );


    if( !ret || ( ( nMonth < 1 ) || ( nMonth > 12 ) ) ) {
        printf("\nInvalid Month");
        return;
    }

    if( ( strlen( prod ) != 6 ) || ( !existsProduct( prodCat, prod ) ) ) {
        printf("\nInvalid Product Code");
        return;
    }

    pr = getProduct( prodCat, prod );

    /* Time Start */
    tStart = clock();

    nSalesP = getMonthSalesPByProduct( acc, pr, nMonth );
    nSalesN = getMonthSalesNByProduct( acc, pr, nMonth );
    total = getMonthProfitByProduct( acc, pr, nMonth );

    count = nSalesP + nSalesN;

    /* Time End */
    parseRunTime( timeS, ( ( (float)clock() - (float)tStart ) / CLOCKS_PER_SEC ) );

    if( !count ) {
        printf("\n No Sales found for given Product/Month");
        return;
    }

    printf("Product: %s\n\t Normal: %d\n\t Promo: %d\n\t Total: %d\n\tProfit: %.2f", prod, nSalesN, nSalesP, count, total );
    printf("\nCompleted in %s", timeS );

	freeProduct(pr);

    getchar();

}

/* Query 4 */
void getUnboughtProducts( Accounting acc )
{
    StringList sl;
    clock_t tStart;
    char timeS[20] = "";

    if( !getAccountingCount( acc ) ) {
        printf("\nAccounting Structure Not Initialized.");
        return;
	}

	/* Time Start */
	tStart = clock();

    sl = getAccountingUnboughtProducts( acc );

    /* Time End */
    parseRunTime( timeS, ( ( (float)clock() - (float)tStart ) / CLOCKS_PER_SEC ) * 1000 );

    if( !getCountStringList( sl ) )
        printf( "\nNo Unbought Products Found." );
    else
        paginateResults( 1, 1, 1, 8, getStringList( sl ), "Products", getCountStringList( sl), timeS );

    freeStringList( sl );
}

/* Query 5 */
void getClientSalesCount( Sales sales, ClientCatalog clientCat )
{
    char client[6] = "";
	ResultsList rl;
	char **lists2;
	int size, i, *cnt;
	Client cli;
	clock_t tStart;
	char timeS[20] = "";


	if( !getClientCount( clientCat ) ) {
        printf("\nClients Catalog Not Initialized.");
        return;
	}

    if( !getSalesCount( sales ) ) {
        printf("\nSales Structure Not Initialized.");
        return;
	}

    printf("\nEnter Client Code: ");
    fgets( client, 6, stdin );

    if( ( strlen( client ) != 5 ) || ( !existsClient( clientCat, client ) ) ) {
        printf("\nInvalid Client Code");
        return;
    }

    /* Time Start */
    tStart = clock();
	cli = getClient(clientCat, client);
	rl = ProductsBoughtByClient(sales, cli);

    /* Time End */
    parseRunTime( timeS, ( ( (float)clock() - (float)tStart ) / CLOCKS_PER_SEC ) * 1000 );

	size = getCountResultsList(rl);

    if( !size ) {
        printf("\nNo Products Found for that Client.");
        freeResultsList( rl );
        return;
    }

	lists2 = malloc(sizeof(char*) * size);
	cnt = getValuesResultsList(rl);
	for (i = 0; i < size; i++)
	{
		lists2[i] = malloc(10);

		sprintf(lists2[i], "%d", cnt[i]);
	}

	paginateResults(2, 0, 1, 10, getDescsResultsList(rl), "Month", size, 10, lists2, "Count", size, timeS );

	printf("Save to File?(Y/N): ");


	if( getchar() == 'Y' ) {

        /* Time Start */
        tStart = clock();

        if( listsToCSV( client, 2, size, getDescsResultsList(rl), "Month", lists2, "Count" ) ) {
            /* Time End */
            parseRunTime( timeS, ( ( (float)clock() - (float)tStart ) / CLOCKS_PER_SEC ) * 1000 );

            printf("\n\tFile Successfully created, %s", timeS );
        }else
            printf("\n\tError Creating File.");

        getchar();
	}
	freeClient(cli);
	freeResultsList( rl );
}

/* Query 6 */
void ClientsByPrefix( ClientCatalog clientCat )
{
	char c;
	StringList l;

    clock_t tStart;
    char timeS[20] = "";

	if( !getClientCount( clientCat ) ) {
        printf("\nClients Catalog Not Initialized.");
        return;
	}

	fflush( stdin );

	printf("\n Enter Client Prefix[A-Z]: ");
	scanf( "%c", &c);

	c = toupper( c );


	if( c >= 'A' && c <= 'Z' ) {
        /* Time Start */
        tStart = clock();
        l = getClientsByPrefix( clientCat, c );

        /* Time End */
        parseRunTime( timeS, ( ( (float)clock() - (float)tStart ) / CLOCKS_PER_SEC ) * 1000 );

		if( getCountStringList( l ) )
            paginateResults( 1, 1, 1, 8, getStringList( l ), "Clientes", getCountStringList( l ), timeS );
        else
            printf("\nNo Clients By That Prefix");

        freeStringList( l );
	}else
		printf("\nInvalid Input");

}

/* Query 7 */
void getSalesInterval( Accounting acc )
{
    int ret;
    int startingMonth, endingMonth;
	StringList sl;
	int i, size;
	char **l, **l1, **l2, **l3;

	clock_t tStart;
	char timeS[20] = "";


    if( !getAccountingCount( acc ) ) {
        printf("\nAccounting Structure Not Initialized.");
        return;
	}

    printf("\n Enter Starting and Finishing Months[1,12]: ");
    ret = scanf("%d %d", &startingMonth, &endingMonth );

    if( (ret != 2 ) || ( endingMonth < startingMonth ) ||
       ( ( startingMonth < 1 ) || ( endingMonth > 12 ) ) ) {
        printf("\nInvalid Month");
        return;
    }

    /* Time Start */
    tStart = clock();

	sl = getIntervalStats(acc, startingMonth, endingMonth);

    /* Time End */
    parseRunTime( timeS, ( ( (float)clock() - (float)tStart ) / CLOCKS_PER_SEC ) * 1000 );

	size = getCountStringList(sl) / 2;
	l = getStringList(sl);
	l1 = malloc(sizeof(char*) * size);
	l2 = malloc(sizeof(char*) * size);
	l3 = malloc(sizeof(char*) * size);
	for (i = 0; i < size; i++)
	{
		l1[i] = l[2 * i];
		l2[i] = l[2 * i + 1];
		l3[i] = getMonthFromInt(startingMonth + i);
	}


	paginateResults(3, 0, 1, 10, l3, "Month", size, 10, l1, "Profit", size, 10, l2, "Count", size, timeS );
}

/* Query 8 */
void getProductBuyers( Sales sales , ProductCatalog pCat )
{
	char product[7];
	char **listN, **listP;
	int cntN, cntP;
	StringList sl1,sl2;

	clock_t tStart;
	char timeS[20] = "";


    if( !getSalesCount( sales ) ) {
        printf("\nSales Structure Not Initialized.");
        return;
	}

	if( !getProductCount( pCat ) ) {
        printf("\nProducts Catalog Not Initialized.");
        return;
	}

	printf("\n Enter Product: ");
	scanf("%s", product);

	if ( !existsProduct( pCat, product ) ) {
        printf("\nNo Product by that Name.");
		return;
	}

    /* Time Start */
    tStart = clock();

	sl1 = productBuyersN(sales, pCat, product);
	sl2 = productBuyersP(sales, pCat, product);

    /* Time End */
    parseRunTime( timeS, ( ( (float)clock() - (float)tStart ) / CLOCKS_PER_SEC ) * 1000 );

	listN = getStringList(sl1);
	listP = getStringList(sl2);
	cntN = getCountStringList(sl1);
	cntP = getCountStringList(sl2);


    if( !cntN && !cntP )
        printf("\nNo Buyers Found for that Product");
    else
        paginateResults(2, 1, 1, 10, listN, "Type N", cntN, 10, listP, "Type P", cntP, timeS );

    freeStringList( sl1 );
    freeStringList( sl2 );
}

/* Query 9 */
void getClientSales(Sales sales, ProductCatalog pCat, ClientCatalog cCat)
{
	char client[6];
	int month;
	int ret, i;
	char **lists, **lists2; int *cnt, size;
	ResultsList mp;

    clock_t tStart;
    char timeS[20] = "";


    if( !getSalesCount( sales ) ) {
        printf("\nSales Structure Not Initialized.");
        return;
	}

	if( !getProductCount( pCat ) ) {
        printf("\nProducts Catalog Not Initialized.");
        return;
	}

    if( !getClientCount( cCat ) ) {
        printf("\nClients Catalog Not Initialized.");
        return;
	}


	do
	{
		printf("\n Enter Client: ");
		ret = scanf("%s", client);
	} while (ret < 1);
	ret = 0;
	do
	{
		printf("\n Enter month[1..12]: ");
		ret = scanf("%d", &month);
	} while (ret < 1);

	if (month > 12 || month < 1)
	{
		printf("\n Invalid month.");
		return;
	}

    /* Time Start */
    tStart = clock();

	mp = mostBoughtMonthlyProductsByClient(sales, cCat, client, month - 1);

    /* Time End */
    parseRunTime( timeS, ( ( (float)clock() - (float)tStart ) / CLOCKS_PER_SEC ) * 1000 );

	lists = getDescsResultsList(mp);
	cnt = getValuesResultsList(mp);
	size = getCountResultsList(mp);

	if( !cnt ) {
        printf("\nNo Products Found by that Client.");
        freeResultsList( mp );
        return;
	}

	lists2 = malloc(sizeof(char*) * size);
	for (i = 0; i < size; i++)
	{
		lists2[i] = malloc(10);

		sprintf(lists2[i], "%d", cnt[i]);
	}

	paginateResults(2, 1, 1, 10, lists, "Products", size, 10 , lists2, "Amount", size, timeS );

	freeResultsList(mp);

	for (i = 0; i < size; i++)
		free(lists2[i]);
	free(lists2);
}

/* Query 10 */
void getActiveClients(Sales sales)
{
	StringList sl;
	char **list;
	int size;

	clock_t tStart;
	char timeS[20] = "";

    if( !getSalesCount( sales ) ) {
        printf("\nSales Structure Not Initialized.");
        return;
	}

    /* Time Start */
    tStart = clock();

	sl = yearRoundClients(sales );

    /* Time End */
    parseRunTime( timeS, ( ( (float)clock() - (float)tStart ) / CLOCKS_PER_SEC ) * 1000 );

	list = getStringList(sl);
	size = getCountStringList(sl);

    if( !size )
        printf("No Active Clients Found.");
    else
        paginateResults( 1, 1, 1, 6, list, "Clients", size, timeS );

    freeStringList( sl );
}

/* Query 11 */
void generateCSV( Accounting acc )
{
	CSV_Stats stats;
	char **l1;
	char **l2;
	char **month;
	int cnt, i;

	clock_t tStart;
	char timeS[20] = "";


    if( !getAccountingCount( acc ) ) {
        printf("\nAccounting Structure Not Initialized.");
        return;
    }

    /* Time Start */
    tStart = clock();

    stats = getMonthsStats( acc );

    /* Time End */
    parseRunTime( timeS, ( ( (float)clock() - (float)tStart ) / CLOCKS_PER_SEC ) * 1000 );

    cnt = getCntCsvStats( stats );

    if( !cnt ) {
        printf("\nAccounting Structure is Empty.");
        freeCsvStats( stats );
        return;
    }

    l1 = getList1CsvStats( stats );
    l2 = getList2CsvStats( stats );

    month = malloc( sizeof(char*) * 12 );

	for (i = 0; i < 12; i++)
	{
		month[i] = malloc(2);
		sprintf(month[i], "%d", i + 1);
	}

	listsToCSV("YearlyStats", 3, cnt,month, "Month", l1, "Clients", l2, "Records");
	freeCsvStats( stats );

	printf("\nFile writen to YearlyStats.csv in %s\n", timeS );
}

/* Query 12 */
void getMostWantedProducts( Sales sales )
{
	Query12 q;
	char **list, **list2, **list3;
	int *iList, *iList2, size, cnt, i;

	clock_t tStart;
	char timeS[20] = "";


    if( !getSalesCount( sales ) ) {
        printf("\nSales Structure Not Initialized.");
        return;
	}

    printf("\n Enter Amount: ");
    scanf("%d", &cnt);


    if( ( cnt <= 0 ) ) {
        printf("\nAmount must be a Number >0.");
        return;
    }
    /* Time Start */
    tStart = clock();

	q = mostSoldProducts(sales, cnt);

    /* Time End */
    parseRunTime( timeS, ( ( (float)clock() - (float)tStart ) / CLOCKS_PER_SEC ) * 1000 );


	size = getQ12Count(q);

	if( !size ) {
        printf("\nNo Sold Products Registered on Accounting.");
        freeQ12( q );
        return;
	}

	list = getQ12StringList(q);
	iList = getQ12UniqueCli(q);
	iList2 = getQ12Units(q);

	list2 = malloc(sizeof(char*)*size);
	for (i = 0; i < size; i++)
	{
		list2[i] = malloc(8);

		sprintf(list2[i], "%d", iList[i]);
	}
	list3 = malloc(sizeof(char*)*size);
	for (i = 0; i < size; i++)
	{
		list3[i] = malloc(8);

		sprintf(list3[i], "%d", iList2[i]);
	}
    if( !size)
        printf("No Products Found.");
    else
		paginateResults(3, 1, 1, 8, list, "Products", size, 8, list3, "Count", size, 8, list2, "Uniques", size, timeS );

	freeQ12(q);
	for (i = 0; i < size; i++)
	{
		free(list2[i]);
	}
	free(list2);
	for (i = 0; i < size; i++)
	{
		free(list3[i]);
	}
	free(list3);

}

/* Query 13 */
void getClientMostWantedProducts( Sales sales , ClientCatalog cCat )
{
	char client[8];
	int ret;
	char **list, **cntL;
	int cnt, *res, i;
	ResultsList rl;
	Client cli;

	clock_t tStart;
	char timeS[20] = "";


	if (!getSalesCount(sales)) {
		printf("\nSales Structure Not Initialized.");
		return;
	}

	if (!getClientCount(cCat)) {
		printf("\nClients Catalog Not Initialized.");
		return;
	}

	printf("\n Enter Client: ");
	ret = scanf("%s", client);

	if (ret == 0)
		return;
	cli = getClient(cCat, client);

	if (!cli) {
        printf("\nNo Client by that Name.");
		return;
	}

    /* Time Start */
    tStart = clock();

	rl = Top3ProductsForClient(sales, cli);

    /* Time End */
    parseRunTime( timeS, ( ( (float)clock() - (float)tStart ) / CLOCKS_PER_SEC ) * 1000 );


	cnt = getCountResultsList(rl);

	if( !cnt ) {
        printf("\nNo Products Found for that Client.");
        freeResultsList( rl );
        return;
	}

	list = getDescsResultsList(rl);
	res = getValuesResultsList(rl);
	cntL = malloc(sizeof(char*)* cnt);
	for (i = 0; i < cnt; i++)
	{
		cntL[i] = malloc(10);
		sprintf(cntL[i], "%d", res[i]);
	}
	paginateResults(2, 1, 1, 10, list, "Product", cnt, 10, cntL, "Count", cnt, timeS );

	for( i = 0; i < cnt; i++ )
        free( cntL[i] );

    free( cntL );

	freeResultsList( rl );
}

/* Query 14 */
void getAllInactive( Sales sales )
{
	StringList s1, s2;
	int sz1, sz2;

	clock_t tStart;
	char timeS[20] = "";


    if( !getSalesCount( sales ) ) {
        printf("\nSales Structure Not Initialized.");
        return;
	}

    /* Time Start */
    tStart = clock();

    s1 = productsWithoutPurchases(sales);
    s2 = clientsWithoutPurchases(sales);

    /* Time End */
    parseRunTime( timeS, ( ( (float)clock() - (float)tStart ) / CLOCKS_PER_SEC ) * 1000 );

    sz1 = getCountStringList( s1 );
    sz2 = getCountStringList( s2 );

    if( !sz1 && !sz2 ) {
        printf("No Products or Clients Without Purchases.");
        return;
    }

	paginateResults( 2,
                 0, 1,
                 8, getStringList( s1 ), "Products", sz1,
                 6, getStringList( s2 ), "Clients", sz2,
                 timeS
    );
}

/*
    usage:
    listsToCSV( "file.txt", 2, 50,
               list1, "titleL1", list2, "titleL2" );
*/
int listsToCSV( char *fileName, int nLists, int listSize, ... )
{
    va_list args;
    char ***lists;
    char **titles;
    char buff[200];
	char *file;
    int i, j;
    FILE *csvFile;
    if( !strlen( fileName ) )
        return 0;
	file = malloc(strlen(fileName) + 5);
	sprintf(file, "%s.csv", fileName);

	lists = (char***)malloc( sizeof( char ** ) * nLists );
	titles = (char**)malloc( sizeof(char*) * nLists );

	va_start( args, listSize );

    /* Grabbing Lists and their titles */
	for( i = 0; i < nLists; i ++) {
        lists[i] = va_arg( args, char** );
        titles[i] = va_arg( args, char* );
	}

	if (!(csvFile = fopen(file, "w")))
       return 0;
	fputs("sep=,\n", csvFile);

    /* Settings Titles */
    for( j = 0; j < nLists; j++ ) {
        if( !j )
            strcpy( buff, titles[j] );
        else
            sprintf( buff, "%s,%s", buff, titles[j] );
    }
    strcat( buff, "\n" );
    fputs( buff, csvFile );

    /* Outputting lines */
    for( i = 0; i < listSize; i++ ) {
        for( j = 0; j < nLists; j++ ) {
            if( !j )
                strcpy( buff, lists[j][i] );
            else
                sprintf( buff, "%s,%s", buff, lists[j][i] );
        }
        strcat( buff, "\n" );
        fputs( buff, csvFile );
    }


    free( titles );

	free(lists);

	free(file);

    fclose( csvFile );

    return 1;
}

/* args: nLists, nPostArgs

	paginateResults(
		2, // nLists
		0, // showIdx
		2, // nPostArgs, shown on footer
            columnSize1, // Max number of chars per entry, title included, works best for pairs
			results1, // firstList
			r1Title, // firstList's title shown on header
			countR1  // n lines in results1

            columnSize2, // Max numbe....
			results2, // secondList
			r2Title, // secondList's title shown on header
			countR2, // n lines in results2

			postArg1, // string, shown on footer
			postArg2, // string, shown on footer

	);
*/

#define CEILING_POS( X, Y ) (1+((X - 1) / Y) )

void paginateResults( int nLists, int showIdx, int nPostArgs, ... )
{
	char header[300] = "";
	char line[300] = "";
	char body[1024] = "";
	char footer[300] = "";
	char ***lists;
	char **postArgs;
	int i, j, nPage;
	va_list args;
	int curPage = 0;
	int maxPage = 0;
	int maxLen = 0;
	char input[10] = "";
	char buf[500] = "";
	char idx[6] = "";
	int *columnSize, *listSize;


    columnSize = (int*)malloc( sizeof(int) * nLists );
    listSize = (int*)malloc( sizeof(int) * nLists );
	lists = (char***)malloc( sizeof( char ** ) * nLists );
	postArgs = (char**)malloc( sizeof(char*) * nPostArgs );

    fflush( stdin );
	va_start( args, nPostArgs );

    if( showIdx ) {
        genColumn( buf, "Indx", 6 );    /* columnSize for Indx is 6 */
        strcat( header, buf);
    }

	for( i = 0; i < nLists; i++ ) {

        columnSize[i] = va_arg( args, int );

        lists[i] = va_arg( args, char** );

        genColumn( buf, va_arg( args, char*), columnSize[i] );

        listSize[i] = va_arg( args, int );

        if( listSize[i] > maxLen )
            maxLen = listSize[i];

        sprintf( header, "%s%s", header, buf );
	}

	for( i = 0; i < nPostArgs; i++ )
        postArgs[i] = va_arg( args, char* );

	maxPage = CEILING_POS( maxLen, (float)PER_PAGE );

	strcat( header, "|\n");

	while( curPage != -1 )
    {

        #if _WIN32
            system("cls");
        #else
            system("clear");
        #endif

		strcpy( body, "" );
		strcpy( footer, "" );
		for( i = curPage * PER_PAGE;
			i < maxLen && i < ( ( curPage + 1 ) * PER_PAGE ) ; i++ )
			{
            strcpy( line, "" );
			if( showIdx ) {
				sprintf( idx, "%d", i + 1);
				genColumn( buf, idx, 6 );   /* columnSize for Indx is 6 */
				strcat( line, buf );
			}

			for( j = 0; j < nLists; j++ ) {
                strcpy( buf, "");

                if( i < listSize[j] )
                    genColumn( buf, lists[j][i], columnSize[j] );
                else
                    genColumn( buf, "-", columnSize[j] );

                strcat( line, buf );
			}
			strcat( line, "|\n" );
			strcat( body, line );

        sprintf( footer, " page %d/%d | %d/%d shown | %d per page", curPage+1, maxPage, i + 1, maxLen, PER_PAGE );

		}


		for( j = 0; j < nPostArgs; j++ ) {
			strcat( footer, " | " );
			strcat( footer, postArgs[j] );
		}

		strcat( footer, "\n(n)ext/(p)revious/(q)uit or page number \n: ");



        sprintf( buf, "|%.*s|", (int)(strlen( header ) - 3), MAX_SEPARATOR );
/*
        strcat( header, buf );
        strcat( body, buf );
*/
        /* sprintf(header, "%s\n|%*.s|\n", header, strlen( header ), MAX_SEPARATOR ); */

        printf("%s%s\n%s%s\n%s", header, buf, body, buf, footer );
		fgets( input, 10, stdin );

		if( ( nPage = atoi( input ) ) == 0 )
			/* Char */
			switch( toupper( input[0] ) ) {

				case 'N': /* next page */
					if( ( curPage + 1 ) < maxPage )
						curPage++;
				break;

				case 'P': /* previous page */
					if( curPage > 0 )
						curPage--;
				break;

				case 'Q': /* quit */
					curPage = -1;
				break;
			}
		else
			/* pageNumber */
			if( ( nPage > 0 ) && ( nPage <= maxPage ) )
				curPage = nPage - 1;

	}


    free( postArgs );

    free( lists );

	free( columnSize );

	free( listSize );

}

void genColumn( char *ret, char *s, int max )
{
    int n = 0;

    n = 1 + (max/2);

    sprintf( ret, "|%*s%*s",
		(int)n + strlen(s) / 2,
        s,
		(int)n - strlen(s) / 2,
    "");

}

void parseRunTime( char *buff, float milis )
{
    if( milis > 1000 )
        sprintf( buff, "(%.2f s)", (float)( (float)milis / (float)1000 ) );
    else
        sprintf( buff, "(%.f ms)", milis );
}

void freeData( ProductCatalog prodCat, ClientCatalog clientCat, Sales sales, Accounting acc )
{

    /*
        TODO: Call Each Catalog's own free function
*/
        freeProductCatalog( prodCat );
        freeClientCatalog( clientCat );
		freeSales(sales);
        freeAccounting(acc);
}
