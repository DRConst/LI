#include "GestHiper.h"
void printMenu();

void readFiles( ProductCatalog prodCat, ClientCatalog clientCat, Sales sales, Accounting acc );
void ProductsByPrefix( ProductCatalog prodCat );
void ClientsByPrefix( ClientCatalog clientCat );
void getProductSalesInfo( ProductCatalog prodCat, Accounting acc );
void getUnboughtProducts( Accounting acc );
void getClientSalesCount( Sales sales, ClientCatalog clientCat );
void getSalesInterval( Sales sales );
void getProductBuyers(Sales sales, ProductCatalog pCat, ClientCatalog cCat);
void getClientSales(Sales sales, ProductCatalog pCat, ClientCatalog cCat);
void getActiveClients(Sales sales, ProductCatalog pCat, ClientCatalog cCat);
void generateCSV( Sales sales, Accounting acc );
void getMostWantedProducts(Sales sales, ProductCatalog pCat, ClientCatalog cCat);
void getClientMostWantedProducts( Sales sales, ClientCatalog cCat );
void getAllInactive( Sales sales );

int listsToCSV( char *fileName, int nLists, int listSize, ... );

void paginateResults( int nLists, int listSize, int showIdx, int postArgs, ... );
void genColumn( char *ret, char *s, int max );
void freeData( ProductCatalog prodCat, ClientCatalog clientCat, Sales sales );


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
					freeData(prodCat, clientCat, sales);

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
                    getSalesInterval( sales );
                break;

                case 8:
					getProductBuyers(sales, prodCat, clientCat);
                break;

                case 9:
					getClientSales(sales, prodCat, clientCat);
                break;

                case 10:
					getActiveClients(sales, prodCat, clientCat);
                break;

                case 11:
                    generateCSV( sales, acc );
                break;

                case 12:
                    getMostWantedProducts( sales, prodCat, clientCat );
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


	printf("\n Optional file paths[Max: %d], enter for default\n", MAX_PATH);

	printf("\n Clients File: ");
	fgets( clients, MAX_PATH, stdin);

	printf("\n Products File: ");
	fgets( products, MAX_PATH, stdin);

	printf("\n Sales File: ");
	fgets( salesFile, MAX_PATH, stdin);

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
    }
    printf("Done \n\t%d read", getSalesCount( sales ) );

    printf("\nOrdering Sales Catalog...");
	sales = orderSales(sales, prodCat, clientCat);
    printf("Done \n");

    printf("\nOrdering Accounting Catalog...");
    acc = orderAcc( acc, prodCat, clientCat );
    printf("Done \n");


    getchar();

}

/* Query 2 */
void ProductsByPrefix( ProductCatalog prodCat )
{
	char c;
	StringList l;

	fflush( stdin );

	if( !getProductCount( prodCat ) ) {
        printf("\nProducts Catalog Not Initialized.");
        return;
	}

	printf("\n Enter Product Prefix[A-Z]: ");
	scanf( "%c", &c);

	c = toupper( c );

	if( c >= 'A' && c <= 'Z' ) {
        l = getProductsByPrefix( prodCat, c );
        if( getCountStringList( l ) )
            paginateResults( 1, getCountStringList( l ), 1, 0, 8, getStringList( l ), "Produtos" );
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

    nSalesP = getMonthSalesPByProduct( acc, pr, nMonth );
    nSalesN = getMonthSalesNByProduct( acc, pr, nMonth );
    total = getMonthProfitByProduct( acc, pr, nMonth );

    count = nSalesP + nSalesN;

    if( !count ) {
        printf("\n No Sales found for given Product/Month");
        return;
    }

    printf("Product: %s\n\t Normal: %d\n\t Promo: %d\n\t Total: %d\n\tProfit: %.2f", prod, nSalesN, nSalesP, count, total );
    getchar();

}

/* Query 4 */
void getUnboughtProducts( Accounting acc )
{
    StringList sl;

    if( !getAccountingCount( acc ) ) {
        printf("\nAccounting Structure Not Initialized.");
        return;
	}

    sl = getAccountingUnboughtProducts( acc );

    paginateResults( 1, getCountStringList( sl), 1, 0, 8, getStringList( sl ), "Products" );

    freeStringList( sl );
}

/* Query 5 */
void getClientSalesCount( Sales sales, ClientCatalog clientCat )
{
    char client[6] = "";
	ResultsList rl;
	char **lists2;
	int size, i, *cnt;
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

	rl = ProductsBoughtByClient(sales, getClient(clientCat, client));
	size = getCountResultsList(rl);
	lists2 = malloc(sizeof(char*) * size);
	cnt = getValuesResultsList(rl);
	for (i = 0; i < size; i++)
	{
		lists2[i] = malloc(10);

		sprintf(lists2[i], "%d", cnt[i]);
	}
	paginateResults(2, size, 0, 0, 10, getDescsResultsList(rl), "Month", 10, lists2, "Count");

	printf("Save to File?(Y/N): ");
	if( getchar() == 'Y' ) {
        if( listsToCSV( client, 2, size, getDescsResultsList(rl), "Month", lists2, "Count" ) )
            printf("\n\tFile Successfully created.");
        else
            printf("\n\tError Creating File.");

        getchar();
	}
}

/* Query 6 */
void ClientsByPrefix( ClientCatalog clientCat )
{
	char c;
	StringList l;


	if( !getClientCount( clientCat ) ) {
        printf("\nClients Catalog Not Initialized.");
        return;
	}

	fflush( stdin );

	printf("\n Enter Client Prefix[A-Z]: ");
	scanf( "%c", &c);

	c = toupper( c );

	if( c >= 'A' && c <= 'Z' ) {
        l = getClientsByPrefix( clientCat, c );
		if( getCountStringList( l ) )
            paginateResults( 1, getCountStringList( l ), 1, 0, 8, getStringList( l ), "Clientes" );
        else
            printf("\nNo Clients By That Prefix");

        freeStringList( l );
	}else
		printf("\nInvalid Input");

}

/* Query 7 */
void getSalesInterval( Sales sales )
{
    int ret;
    int startingMonth, endingMonth;


    if( !getSalesCount( sales ) ) {
        printf("\nSales Structure Not Initialized.");
        return;
	}

    printf("\n Enter Starting and Finishing Months[1,12]: ");
    ret = scanf("%d %d", &startingMonth, &endingMonth );

    if( (ret != 2 ) || ( endingMonth < startingMonth ) ||
       ( ( startingMonth < 1 ) || ( endingMonth > 12 ) ) ) {
        printf("\nInvalid Month");
        return;
    }
}

/* Query 8 */
void getProductBuyers( Sales sales , ProductCatalog pCat, ClientCatalog cCat )
{
	char product[7];
	int ret;
	char **listN, **listP;
	int cntN, cntP;
	StringList sl1,sl2;


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

	printf("\n Enter Product: ");
	ret = scanf("%s", product);

	if (ret == 0)
		return;

	sl1 = productBuyersN(sales, pCat, cCat, product);
	sl2 = productBuyersP(sales, pCat, cCat, product);

	listN = getStringList(sl1);
	listP = getStringList(sl2);
	cntN = getCountStringList(sl1);
	cntP = getCountStringList(sl2);

	paginateResults(1, cntN, 1, 0, 10, listN, "Type N");
	paginateResults(1, cntP, 1, 0, 10, listP, "Type P");
}

/* Query 9 */
void getClientSales(Sales sales, ProductCatalog pCat, ClientCatalog cCat)
{
	char client[6];
	int month;
	int ret, i;
	char **lists, **lists2; int *cnt, size;
	ResultsList mp;


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

	mp = mostBoughtMonthlyProductsByClient(sales, pCat, cCat, client, month - 1);
	lists = getDescsResultsList(mp);
	cnt = getValuesResultsList(mp);
	size = getCountResultsList(mp);
	lists2 = malloc(sizeof(char*) * size);
	for (i = 0; i < size; i++)
	{
		lists2[i] = malloc(10);

		sprintf(lists2[i], "%d", cnt[i]);
	}
	paginateResults(2, size, 1, 0, 10, lists, "Products", 10 , lists2, "Amount");
	freeResultsList(mp);
	for (i = 0; i < size; i++)
		free(lists2[i]);
	free(lists2);
}

/* Query 10 */
void getActiveClients(Sales sales, ProductCatalog pCat, ClientCatalog cCat)
{
	StringList sl;
	char **list;
	int size;


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


	sl = yearRoundClients(sales, pCat, cCat);
	list = getStringList(sl);
	size = getCountStringList(sl);

    if( !size )
        printf("No Active Clients Found.");
    else
        paginateResults( 1, size, 1, 0, 6, list, "Clients" );
}

/* Query 11 */
void generateCSV( Sales sales, Accounting acc)
{
	CSV_Stats stats = getMonthsStats(acc);
	char **l1 = getList1CsvStats(stats);
	char **l2 = getList2CsvStats(stats);
	char **month = malloc(sizeof(char *) * 12);
	int cnt = getCntCsvStats(stats), i;

	for (i = 0; i < 12; i++)
	{
		month[i] = malloc(2);
		sprintf(month[i], "%d", i + 1);
	}
	//paginateResults(2, cnt, 1, 0, 10, l1, "", 10, l2, "");
	listsToCSV("YearlyStats", 3, cnt,month, "Month", l1, "Clients", l2, "Records");
	printf("\nFile writen to YearlyStats.csv\n");
}

/* Query 12 */
void getMostWantedProducts(Sales sales, ProductCatalog pCat, ClientCatalog cCat)
{
	ResultsList sl;
	char **list, **list2;
	int *iList,size, cnt, ret, i;


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
		printf("\n Enter Ammount: ");
		ret = scanf("%d", &cnt);
	} while (ret < 1);

	sl = mostSoldProducts(sales, pCat, cCat, cnt);
	list = getDescsResultsList(sl);
	iList = getValuesResultsList(sl);
	size = getCountResultsList(sl);
	list2 = malloc(sizeof(char*)*size);
	for (i = 0; i < size; i++)
	{
		list2[i] = malloc(8);

		sprintf(list2[i], "%d", iList[i]);
	}
    if( !size)
        printf("No Products Found.");
    else
		paginateResults(2, size, 1, 0, 8, list, "Products", 8, list2, "Count");
	freeResultsList(sl);
	for (i = 0; i < size; i++)
	{
		free(list2[i]);
	}
	free(list2);
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
	if (!getSalesCount(sales)) {
		printf("\nSales Structure Not Initialized.");
		return;
	}

	if (!getClientCount(cCat)) {
		printf("\nClients Catalog Not Initialized.");
		return;
	}

	printf("\n Enter Product: ");
	ret = scanf("%s", client);

	if (ret == 0)
		return;
	cli = getClient(cCat, client);
	if (!cli)
		return;
	rl = Top3ProductsForClient(sales, cli);
	list = getDescsResultsList(rl);
	cnt = getCountResultsList(rl);
	res = getValuesResultsList(rl);
	cntL = malloc(sizeof(char*)* cnt);
	for (i = 0; i < 12; i++)
	{
		cntL[i] = malloc(10);
		sprintf(cntL[i], "%d", res[i]);
	}
	paginateResults(2, cnt, 1, 0, 10, list, "Product", 10, cntL, "Count");
}

/* Query 14 */
void getAllInactive( Sales sales )
{
	StringList s1, s2;
	int sz1, sz2;


    if( !getSalesCount( sales ) ) {
        printf("\nSales Structure Not Initialized.");
        return;
	}

    s1 = productsWithoutPurchases(sales);
    s2 = clientsWithoutPurchases(sales);

    sz1 = getCountStringList( s1 );
    sz2 = getCountStringList( s2 );

    if( !sz1 && !sz2 ) {
        printf("No Products or Clients Without Purchases.");
        return;
    }

	paginateResults( 2, ( (sz1 > sz2) ? sz1 : sz2),
                 0, 0,
                 8, getStringList( s1 ), "Products",
                 6, getStringList( s2 ), "Clients"
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
		50, // eachListSize
		0, // showIdx
		2, // nPostArgs, shown on footer
            columnSize1, // Max number of chars per entry, title included, works best for pairs
			results1, // firstList
			r1Title, // firstList's title shown on header

            columnSize2, // Max numbe....
			results2, // secondList
			r2Title, // secondList's title shown on header

			postArg1, // string, shown on footer
			postArg2, // string, shown on footer

	);
*/

#define CEILING_POS( X, Y ) (1+((X - 1) / Y) )

void paginateResults( int nLists, int listSize, int showIdx, int postArgs, ... )
{
	char header[300] = "";
	char line[300] = "";
	char body[1024] = "";
	char footer[300] = "";
	char ***lists;
	int i, j, nPage;
	va_list args;
	int curPage = 0;
/*	int maxPage = ceil( (listSize / (float)PER_PAGE ) ); */
	int maxPage = CEILING_POS( listSize, (float)PER_PAGE );
	char input[10] = "";
	char buf[500] = "";
	char idx[6] = "";
	int *columnSize;


    columnSize = (int*)malloc( sizeof(int) * nLists );
	lists = (char***)malloc( sizeof( char ** ) * nLists );

    fflush( stdin );
	va_start( args, postArgs );

    if( showIdx ) {
        genColumn( buf, "Indx", 6 );    /* columnSize for Indx is 6 */
        strcat( header, buf);
    }

	for( i = 0; i < nLists; i++ ) {

        columnSize[i] = va_arg( args, int );

        lists[i] = va_arg( args, char** );

        genColumn( buf, va_arg( args, char*), columnSize[i] );

        sprintf( header, "%s%s", header, buf );
	}

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
			i < listSize && i < ( ( curPage + 1 ) * PER_PAGE ) ; i++ )
			{
            strcpy( line, "" );
			if( showIdx ) {
				sprintf( idx, "%d", i + 1);
				genColumn( buf, idx, 6 );   /* columnSize for Indx is 6 */
				strcat( line, buf );
			}

			for( j = 0; j < nLists; j++ ) {
                strcpy( buf, "");
                genColumn( buf, lists[j][i], columnSize[j] );
                strcat( line, buf );
			}
			strcat( line, "|\n" );
			strcat( body, line );

        sprintf( footer, " page %d/%d | %d/%d shown | %d per page", curPage+1, maxPage, i + 1, listSize, PER_PAGE );

		}


		for( j = 0; j < postArgs; j++ ) {
			strcat( footer, " | " );
			strcat( footer, va_arg( args, char* ) );
		}

		strcat( footer, "\n(n)ext/(p)revious/(q)uit or page number \n: ");



        sprintf( buf, "|%.*s|", strlen( header ) - 3, MAX_SEPARATOR );
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



    free( lists );

	free( columnSize );

}

void genColumn( char *ret, char *s, int max )
{
    int n = 0;

    n = 1 + (max/2);

    sprintf( ret, "|%*s%*s",
        n + strlen(s)/2,
        s,
        n - strlen(s)/2,
    "");

}

void freeData( ProductCatalog prodCat, ClientCatalog clientCat, Sales sales )
{

    /*
        TODO: Call Each Catalog's own free function
*/
        freeProductCatalog( prodCat );
        freeClientCatalog( clientCat );
		freeSales(sales);
/*
        freeAccounting( &sales );

    */
}
