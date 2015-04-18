#include "GestHiper.h"

void printMenu();

void readFiles( ProductCatalog prodCat, ClientCatalog clientCat, Sales sales );
void ProductsByPrefix( ProductCatalog prodCat );
void ClientsByPrefix( ClientCatalog clientCat );
void getProductSalesInfo( ProductCatalog prodCat, Sales sales );
void getUnboughtProducts( Sales sales );
void getClientSalesCount( Sales sales, ClientCatalog clientCat );
void getSalesInterval( Sales sales );
void getProductBuyers(Sales sales, ProductCatalog pCat, ClientCatalog cCat);
void getClientSales(Sales sales, ProductCatalog pCat, ClientCatalog cCat);
void getActiveClients(Sales sales, ProductCatalog pCat, ClientCatalog cCat);
void generateCSV( Sales sales );
void getMostWantedProducts(Sales sales, ProductCatalog pCat, ClientCatalog cCat);
void getClientMostWantedProducts( Sales sales );
void getAllInactive( Sales sales );

void paginateResults( int nLists, int listSize, int showIdx, int postArgs, ... );
void genColumn( char *ret, char *s, int max );
void freeData( ProductCatalog prodCat, ClientCatalog clientCat, Sales sales );


int main()
{
	int op = 1;
    ProductCatalog prodCat = initProductCatalog();
    ClientCatalog clientCat = initClientCatalog();
    Sales sales = initSales();
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
/*					freeData(prodCat, clientCat, sales);  */

					prodCat = initProductCatalog();

					clientCat = initClientCatalog();

					sales = initSales();

                    readFiles( prodCat, clientCat, sales );
                break;

                case 2:
                    ProductsByPrefix( prodCat );
                break;

                case 3:
                    getProductSalesInfo( prodCat, sales );
                break;

                case 4:
                    getUnboughtProducts( sales );
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
                    generateCSV( sales );
                break;

                case 12:
                    getMostWantedProducts( sales, prodCat, clientCat );
                break;

                case 13:
                    getClientMostWantedProducts( sales );
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
void readFiles( ProductCatalog prodCat, ClientCatalog clientCat, Sales sales )
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
        if( isalpha( buff[0] ) && isalpha( buff[1] ) &&
          isdigit( buff[2] ) && isdigit( buff[3] ) &&
          isdigit( buff[4] ) && isdigit( buff[5] ) )

            prodCat = insertProduct( prodCat, buff);
    }
    printf("Done \n\t%d read", getProductCount( prodCat ) );

    printf("\nReading Clients Catalog...");
    while( fgets(buff, 7, clientsFp ) )
    {
        if( isalpha( buff[0] ) && isalpha( buff[1] ) &&
          isdigit( buff[2] ) && isdigit( buff[3] ) &&
          isdigit( buff[4] ) )

            clientCat = insertClient( clientCat, buff);
    }
    printf("Done \n\t%d read", getClientCount( clientCat ) );

    printf("\nReading Sales Catalog...");
    while( fgets( buff, 64, salesFp ) )
    {
        ret = sscanf( buff, "%s %lf %d %c %s %d", prod, &price, &qtd, &type, client, &month );

        sale = createSale( month, qtd, price, prod, client, type );

        if( ret == 6 )
            addSale( sales, clientCat, prodCat,
                    sale
            );
    }
    printf("Done \n\t%d read", getSalesCount( sales ) );
    printf("\nOrdering Sales Catalog...");
	orderAcc(sales, prodCat, clientCat);
    printf("Done \n");
    /*
        TODO:
            Process Sales File

            Do Sales

    */


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
void getProductSalesInfo( ProductCatalog prodCat, Sales sales )
{
    int nMonth = 0;
    char prod[7] = "";
    int ret;
    int nSalesP, nSalesN, count;
    double total;

	if( !getProductCount( prodCat ) ) {
        printf("\nProducts Catalog Not Initialized.");
        return;
	}

    if( !getSalesCount( sales ) ) {
        printf("\nSales Structure Not Initialized.");
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

    count = getProductSalesPerMonth( sales, (getProduct( prodCat, prod)), nMonth, &nSalesP, &nSalesN, &total );

    if( !count ) {
        printf("\n No Sales found for given Product/Month");
        return;
    }

    printf("Product: %s\n\t Normal: %d\n\t Promo: %d\n\t Total: %d\n\tProfit: %.2f", prod, nSalesN, nSalesP, count, total );
    getchar();

}

/* Query 4 */
void getUnboughtProducts( Sales sales )
{

    if( !getSalesCount( sales ) ) {
        printf("\nSales Structure Not Initialized.");
        return;
	}
}

/* Query 5 */
void getClientSalesCount( Sales sales, ClientCatalog clientCat )
{
    char client[6] = "";


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

    if( ( strlen( client ) != 6 ) || ( !existsClient( clientCat, client ) ) ) {
        printf("\nInvalid Client Code");
        return;
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
	ProductBuyers pB;


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

	pB = productBuyers(sales, pCat, cCat, product);

	listN = getProductBuyersN(pB);
	listP = getProductBuyersP(pB);
	cntN = getProductBuyersCntN(pB);
	cntP = getProductBuyersCntP(pB);

	paginateResults(1, cntN, 1, 0, 10, listN, "Type N");
	paginateResults(1, cntP, 1, 0, 10, listP, "Type P");
}

/* Query 9 */
void getClientSales(Sales sales, ProductCatalog pCat, ClientCatalog cCat)
{
	char client[6];
	int month;
	int ret;
	char **lists; int *cnt, size;
	Monthly_Purchases mp;


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
	lists = getMonthlyPurchasesList(mp);
	cnt = getMonthlyPurchasesCounts(mp);
	size = getMonthlyPurchasesSize(mp);
	paginateResults(2, size, 1, 0, 10, lists, "Products", 10 , cnt, "Ammount");

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
void generateCSV( Sales sales )
{

}

/* Query 12 */
void getMostWantedProducts(Sales sales, ProductCatalog pCat, ClientCatalog cCat)
{
	StringList sl = mostSoldProducts(sales, pCat, cCat, 5);
	char **list = getStringList(sl);
	int size = getCountStringList(sl);


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


    if( !size)
        printf("No Products Found.");
    else
        paginateResults( 1, size, 1, 0, 8, list, "Products" );
}

/* Query 13 */
void getClientMostWantedProducts( Sales sales )
{

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


	for( i = 0; i < nLists; i++ ) {

        for( j = 0; j < listSize; j++ )
            free( lists[i][j] );

        free( lists[i] );
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
/*
        freeAccounting( &sales );

    */

}
