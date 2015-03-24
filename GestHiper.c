#include "GestHiper.h"

void printMenu();

void readFiles( ProductCatalog **prodCat, ClientCatalog **clientCat, Accounting **acc );
void getProductsByPrefix( ProductCatalog *prodCat );
void getClientsByPrefix( ClientCatalog *clientCat );
void getProductSalesInfo( ProductCatalog *prodCat, Accounting *acc );
void getUnboughtProducts( Accounting *acc );
void getClientSalesCount( Accounting *acc, ClientCatalog *clientCat );
void getSalesInterval( Accounting *acc );
void getProductBuyers( Accounting *acc );
void getClientSales( Accounting *acc );
void getActiveClients( Accounting *acc );
void generateCSV( Accounting *acc );
void getMostWantedProducts( Accounting *acc );
void getClientMostWantedProducts( Accounting *acc );
void getAllInactive( Accounting *acc );

void paginateResults( int nLists, int listSize, int showIdx, int postArgs, ... );
void genColumn( char *ret, char *s, int max );
void freeData( ProductCatalog **prodCat, ClientCatalog **clientCat, Accounting **acc );


int main()
{
	int op = 1;
    ProductCatalog *prodCat = initProductCatalog();
    ClientCatalog *clientCat = initClientCatalog();
    Accounting *acc = initAccounting();
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
                    readFiles( &prodCat, &clientCat, &acc );
                break;

                case 2:
                    getProductsByPrefix( prodCat );
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
                    getClientsByPrefix( clientCat );
                break;

                case 7:
                    getSalesInterval( acc );
                break;

                case 8:
                    getProductBuyers( acc );
                break;

                case 9:
                    getClientSales( acc );
                break;

                case 10:
                    getActiveClients( acc );
                break;

                case 11:
                    generateCSV( acc );
                break;

                case 12:
                    getMostWantedProducts( acc );
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

    freeData( &prodCat, &clientCat, &acc );

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




void readFiles( ProductCatalog **prodCat, ClientCatalog **clientCat, Accounting **acc )
{
	char clients[MAX_PATH] = "";
	char products[MAX_PATH] = "";
	char sales[MAX_PATH] = "";
	char buff[8];
	FILE *clientsFp, *productsFp, *salesFp;

    char type;
    int qtd, month, ret;
    char prod[7], client[6];
    double price;
    Sale *sale;


    freeData( prodCat, clientCat, acc );

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
    *prodCat = initProductCatalog();
    while( fgets(buff, 8, productsFp ) )
    {
        if( isalpha( buff[0] ) && isalpha( buff[1] ) &&
          isdigit( buff[2] ) && isdigit( buff[3] ) &&
          isdigit( buff[4] ) && isdigit( buff[5] ) )

            *prodCat = insertProduct( *prodCat, buff);
    }
    printf("Done \n\t%d read", getProductCount( *prodCat ) );

    printf("\nReading Clients Catalog...");
    *clientCat = initClientCatalog();
    while( fgets(buff, 7, clientsFp ) )
    {
        if( isalpha( buff[0] ) && isalpha( buff[1] ) &&
          isdigit( buff[2] ) && isdigit( buff[3] ) &&
          isdigit( buff[4] ) )

            *clientCat = insertClient( *clientCat, buff);
    }
    printf("Done \n\t%d read", getClientCount( *clientCat ) );

    printf("\nReading Sales Catalog...");
    *acc = initAccounting();
    while( fgets( buff, 64, salesFp ) )
    {
        ret = sscanf( buff, "%s %lf %d %c %s %d", prod, &price, &qtd, &type, client, &month );

        sale = createSale( month, qtd, price, prod, client, type );
        printf("\n%d", getSalesCount( acc ) );
        if( ret == 6 )
            addSale( *acc, *clientCat, *prodCat,
                    sale
            );
    }
    printf("Done \n\t%d read", getSalesCount( acc ) );
    /*
        TODO:
            Process Sales File

            Do Accounting

	*/

    getchar();

}


void getProductsByPrefix( ProductCatalog *prodCat )
{
	char c;
	int cnt = 0;
	char **res;

	fflush( stdin );

	if( !getProductCount( prodCat ) ) {
        printf("\nProducts Catalog Not Initialized.");
        return;
	}

	printf("\n Enter Product Prefix[A-Z]: ");
	scanf( "%c", &c);

	c = toupper( c );

	if( c >= 'A' && c <= 'Z' ) {
        res = query2( prodCat, c, &cnt );
        if( cnt )
            paginateResults( 1, cnt, 1, 0, 8, res, "Produtos" );
        else
            printf( "\nNo Products By That Prefix" );
	}else
		printf("\nInvalid Input");

}


void getProductSalesInfo( ProductCatalog *prodCat, Accounting *acc )
{
    int nMonth = 0;
    char prod[7] = "";
    int ret;

	if( !getProductCount( prodCat ) ) {
        printf("\nClients Catalog Not Initialized.");
        return;
	}

    if( !getSalesCount( acc ) ) {
        printf("\nAccounting Structure Not Initialized.");
        return;
	}

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

    printf("\n All's well");

}


void getUnboughtProducts( Accounting *acc )
{
}


void getClientSalesCount( Accounting *acc, ClientCatalog *clientCat )
{
    char client[6] = "";


    printf("\nEnter Client Code: ");
    fgets( client, 6, stdin );

    if( ( strlen( client ) != 6 ) || ( !existsClient( clientCat, client ) ) ) {
        printf("\nInvalid Client Code");
        return;
    }


}


void getClientsByPrefix( ClientCatalog *clientCat )
{
	char c;
	int cnt;
	char **res;

	fflush( stdin );

	printf("\n Enter Client Prefix[A-Z]: ");
	scanf( "%c", &c);

	c = toupper( c );

	if( c >= 'A' && c <= 'Z' ) {
        res = query6( clientCat, c, &cnt );
		if( cnt )
            paginateResults( 1, cnt, 1, 0, 8, res, "Clientes" );
        else
            printf("\nNo Clients By That Prefix");
	}else
		printf("\nInvalid Input");

}


void getSalesInterval( Accounting *acc )
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


void getProductBuyers( Accounting *acc )
{

}


void getClientSales( Accounting *acc )
{

}


void getActiveClients( Accounting *acc )
{

}


void generateCSV( Accounting *acc )
{

}


void getMostWantedProducts( Accounting *acc )
{

}


void getClientMostWantedProducts( Accounting *acc )
{

}


void getAllInactive( Accounting *acc )
{

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
	int maxPage = ceil( (listSize / (float)PER_PAGE ) );
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
					if( curPage < maxPage )
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

	for( i = 0; i < nLists; i++ )
        for( j = 0; j < listSize; j++ )
            free( lists[i][j] );

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

void freeData( ProductCatalog **prodCat, ClientCatalog **clientCat, Accounting **acc )
{

    /*
        TODO: Call Each Catalog's own free function

        freeProductCatalog( &prodCat );
        freeClientCatalog( &clientCat );
        freeAccounting( &acc );

    */

}
