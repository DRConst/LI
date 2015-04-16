#include "GestHiper.h"

void printMenu();

void readFiles( ProductCatalog prodCat, ClientCatalog clientCat, Accounting acc );
void ProductsByPrefix( ProductCatalog prodCat );
void ClientsByPrefix( ClientCatalog clientCat );
void getProductSalesInfo( ProductCatalog prodCat, Accounting acc );
void getUnboughtProducts( Accounting acc );
void getClientSalesCount( Accounting acc, ClientCatalog clientCat );
void getSalesInterval( Accounting acc );
void getProductBuyers(Accounting acc, ProductCatalog pCat, ClientCatalog cCat);
void getClientSales(Accounting acc, ProductCatalog pCat, ClientCatalog cCat);
void getActiveClients(Accounting acc, ProductCatalog pCat, ClientCatalog cCat);
void generateCSV( Accounting acc );
void getMostWantedProducts(Accounting acc, ProductCatalog pCat, ClientCatalog cCat);
void getClientMostWantedProducts( Accounting acc );
void getAllInactive( Accounting acc );

void paginateResults( int nLists, int listSize, int showIdx, int postArgs, ... );
void genColumn( char *ret, char *s, int max );
void freeData( ProductCatalog prodCat, ClientCatalog clientCat, Accounting acc );


int main()
{
	int op = 1;
    ProductCatalog prodCat = initProductCatalog();
    ClientCatalog clientCat = initClientCatalog();
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
/*					freeData(prodCat, clientCat, acc);  */

					prodCat = initProductCatalog();

					clientCat = initClientCatalog();

					acc = initAccounting();

                    readFiles( prodCat, clientCat, acc );
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
                    getClientSalesCount( acc, clientCat );
                break;

                case 6:
                    ClientsByPrefix( clientCat );
                break;

                case 7:
                    getSalesInterval( acc );
                break;

                case 8:
					getProductBuyers(acc, prodCat, clientCat);
                break;

                case 9:
					getClientSales(acc, prodCat, clientCat);
                break;

                case 10:
					getActiveClients(acc, prodCat, clientCat);
                break;

                case 11:
                    generateCSV( acc );
                break;

                case 12:
                    getMostWantedProducts( acc, prodCat, clientCat );
                break;

                case 13:
                    getClientMostWantedProducts( acc );
                break;

                case 14:
                    getAllInactive( acc );
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




void readFiles( ProductCatalog prodCat, ClientCatalog clientCat, Accounting acc )
{
	char clients[MAX_PATH] = "";
	char products[MAX_PATH] = "";
	char sales[MAX_PATH] = "";
	FILE *clientsFp, *productsFp, *salesFp;

    char type;
    int qtd, month, ret;
    char prod[7], client[6], buff[128];
    double price;
    Sale *sale;


	printf("\n Optional file paths[Max: %d], enter for default\n", MAX_PATH);

	printf("\n Clients File: ");
	fgets( clients, MAX_PATH, stdin);

	printf("\n Products File: ");
	fgets( products, MAX_PATH, stdin);

	printf("\n Sales File: ");
	fgets( sales, MAX_PATH, stdin);


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


    if( strlen( sales ) == 1 )
        strcpy( sales, "Compras.txt" );

    if( ( salesFp = fopen( sales, "r" ) ) == NULL ) {
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
            addSale( acc, clientCat, prodCat,
                    sale
            );
    }
    printf("Done \n\t%d read", getSalesCount( acc ) );
    printf("\nOrdering Sales Catalog...");
	orderAcc(acc, prodCat, clientCat);
    printf("Done \n");
    /*
        TODO:
            Process Sales File

            Do Accounting

    */


    getchar();

}


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


void getProductSalesInfo( ProductCatalog prodCat, Accounting acc )
{
    int nMonth = 0;
    char prod[7] = "";
    int ret;
    int nSalesP, nSalesN, count;
    double total;

	if( !getProductCount( prodCat ) ) {
        printf("\nClients Catalog Not Initialized.");
        return;
	}

    if( !getSalesCount( acc ) ) {
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

    count = getProductSalesPerMonth( acc, (getProduct( prodCat, prod)), nMonth, &nSalesP, &nSalesN, &total );

    if( !count ) {
        printf("\n No Sales found for given Product/Month");
        return;
    }

    printf("Product: %s\n\t Normal: %d\n\t Promo: %d\n\t Total: %d\n\tProfit: %.2f", prod, nSalesN, nSalesP, count, total );
    getchar();

}


void getUnboughtProducts( Accounting acc )
{
}


void getClientSalesCount( Accounting acc, ClientCatalog clientCat )
{
    char client[6] = "";


    printf("\nEnter Client Code: ");
    fgets( client, 6, stdin );

    if( ( strlen( client ) != 6 ) || ( !existsClient( clientCat, client ) ) ) {
        printf("\nInvalid Client Code");
        return;
    }


}


void ClientsByPrefix( ClientCatalog clientCat )
{
	char c;
	StringList l;

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


void getSalesInterval( Accounting acc )
{
    int ret;
    int startingMonth, endingMonth;


    printf("\n Enter Starting and Finishing Months[1,12]: ");
    ret = scanf("%d %d", &startingMonth, &endingMonth );

    if( (ret != 2 ) || ( endingMonth < startingMonth ) ||
       ( ( startingMonth < 1 ) || ( endingMonth > 12 ) ) ) {
        printf("\nInvalid Month");
        return;
    }
}


void getProductBuyers( Accounting acc , ProductCatalog pCat, ClientCatalog cCat )
{
	char product[7];
	int ret;

	printf("\n Enter Product: ");
	ret = scanf("%s", product);

	ProductBuyers pB = productBuyers(acc, pCat, cCat, product);
}


void getClientSales(Accounting acc, ProductCatalog pCat, ClientCatalog cCat)
{
	char client[6];
	int month;
	int ret,i = 0;
	char **lists; int *cnt, size;
	Monthly_Purchases mp;
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

	mp = mostBoughtMonthlyProductsByClient(acc, pCat, cCat, client, month - 1);
	lists = getMonthlyPurchasesList(mp);
	cnt = getMonthlyPurchasesCounts;
	size = getMonthlyPurchasesSize(mp);
	/*TODO PAGINATE*/
	/*placeholder*/

}


void getActiveClients(Accounting acc, ProductCatalog pCat, ClientCatalog cCat)
{
	StringList sl = yearRoundClients(acc, pCat, cCat);
	char **list = getStringList(sl);
	int size = getCountStringList(sl), i;


    if( !size )
        printf("No Active Clients Found.");
    else
        paginateResults( 1, size, 1, 0, 6, list, "Clients" );
}


void generateCSV( Accounting acc )
{

}


void getMostWantedProducts(Accounting acc, ProductCatalog pCat, ClientCatalog cCat)
{
	StringList sl = mostSoldProducts(acc, pCat, cCat, 5);
	char **list = getStringList(sl);
	int size = getCountStringList(sl), i;


    if( !size)
        printf("No Products Found.");
    else
        paginateResults( 1, size, 1, 0, 8, list, "Products" );
}


void getClientMostWantedProducts( Accounting acc )
{

}


void getAllInactive( Accounting acc )
{
	StringList s1 = productsWithoutPurchases(acc);
	StringList s2 = clientsWithoutPurchases(acc);
	char **l1 = getStringList(s1), **l2 = getStringList(s2);
	int sz1 = getCountStringList(s1), sz2 = getCountStringList(s2), i;


	paginateResults( 2, ( (sz1 > sz2) ? sz1 : sz2),
                 0, 0,
                 8, l1, "Products",
                 6, l2, "Clients"
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

void freeData( ProductCatalog prodCat, ClientCatalog clientCat, Accounting acc )
{

    /*
        TODO: Call Each Catalog's own free function
*/
        freeProductCatalog( prodCat );
        freeClientCatalog( clientCat );
/*
        freeAccounting( &acc );

    */

}
