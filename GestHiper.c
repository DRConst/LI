#include "GestHiper.h"

void printMenu();
void readFiles( ProductCatalog *productCat, ClientCatalog *clientCat );
void getProductsByPrefix();
void getClientsByPrefix();
void paginateResults( int nLists, int listSize, int showIdx, int postArgs, ... );

int main()
{
	int op;
    ProductCatalog *productCat;
    ClientCatalog *clientCat;





	do {
		printMenu();
		scanf("%d", &op );

        #if _WIN32
            system("cls");
        #else
            system("clear")
        #endif

		switch( op ) {

			case 1:
				printf(" on 1");
				readFiles( productCat, clientCat );
			break;

			case 2:
				printf(" on 2");
				getProductsByPrefix();
			break;

			case 3:
				printf(" on 3");
			break;

			case 4:
				printf(" on 4");
			break;

			case 5:
				printf(" on 5");
			break;

			case 6:
				printf(" on 6");
				getClientsByPrefix();
			break;

			case 7:
				printf(" on 7");
			break;

			case 8:
				printf(" on 8");
			break;

			case 9:
				printf(" on 9");
			break;

			case 10:
				printf(" on 10");
			break;

			case 11:
				printf(" on 11");
			break;

			case 12:
				printf(" on 12");
			break;

			case 13:
				printf(" on 13");
			break;

			case 14:
				printf(" on 14");
			break;

			case 0:
			break;
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

void readFiles( ProductCatalog *productCat, ClientCatalog *clientCat )
{
	char clients[MAX_PATH] = "";
	char products[MAX_PATH] = "";
	char sales[MAX_PATH] = "";

	char buff[8];
	FILE *clientsFp, *productsFp, *salesFp;

    fflush(stdin);

	printf("\n Optional file paths[Max: MAX_PATH], enter for default");

	printf("\n Clients File: ");
	fgets( clients, MAX_PATH, stdin);

	printf("\n Products File: ");
	fgets( products, MAX_PATH, stdin);
/*
	printf("\n Sales File: ");
	fgets( sales, MAX_PATH, stdin);
*/

    if( strlen( clients ) == 1 )
        clientsFp = fopen("FichClientes.txt", "r" );
    else
        clientsFp = fopen( clients , "r" );

    if( clientsFp == NULL ) {
        printf( "\nClients File Not Found");
        return;
    }

    if( strlen( products ) == 1 )
        productsFp = fopen("FichProdutos.txt", "r" );
    else
        productsFp = fopen( products , "r" );

    if( productsFp == NULL ) {
        printf( "\nProducts File Not Found");
        return;
    }

    if( !strlen( sales ) )
        salesFp = fopen("Compras.txt", "r" );
    else
        salesFp = fopen( sales , "r" );

    if( salesFp == NULL ) {
        printf( "\nSales File Not Found");
        return;
    }


    productCat = initProductCatalog(NULL);
    while( fgets(buff, 8, productsFp ) )
    {
        if( isalpha( buff[0] ) && isalpha( buff[1] ) &&
          isdigit( buff[2] ) && isdigit( buff[3] ) &&
          isdigit( buff[4] ) && isdigit( buff[5] ) )

            productCat = insertProduct(productCat, buff);
    }

    clientCat = initClientCatalog(NULL);
    while( fgets(buff, 7, clientsFp ) )
    {
        if( isalpha( buff[0] ) && isalpha( buff[1] ) &&
          isdigit( buff[2] ) && isdigit( buff[3] ) &&
          isdigit( buff[4] ) )

            clientCat = insertClient(clientCat, buff);
    }

    printf("all done");
    /*
        TODO:
            Process Sales File

            Do Accounting

	*/
}

void getProductsByPrefix( ProductCatalog *productCat )
{
	char c;
	int cnt;
	char **res;

	fflush( stdin );

	printf("\n Enter Prefix[A-Z]: ");
	scanf( "%c", &c);

	c = toupper( c );
    printf( "prefix: %c", c);
	if( c >= 'A' && c <= 'Z' ) {
        res = query2( productCat, c, &cnt );printf("past query2");
		paginateResults( 1, cnt, 1, 1, res, "Produtos", cnt );
	}else
		printf("\nInvalid Input");

}

void getClientsByPrefix( ClientCatalog *clientCat )
{
	char c;
	int cnt;
	char **res;

	fflush( stdin );

	printf("\n Enter Prefix[A-Z]: ");
	scanf( "%c", &c);

	c = toupper( c );

	if( c >= 'A' && c <= 'Z' ) {
        res = query6( clientCat, c, &cnt );
		paginateResults( 1, cnt, 1, 1, res, "Clientes", cnt );
	}else
		printf("\nInvalid Input");

}

/* args: nLists, nPostArgs

	paginateResults(
		2, // nLists
		50, // eachListSize
		0, // showIdx
		2, // nPostArgs, shown on footer
			results1, // firstList
			r1Title, // firstList's title shown on header

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
	int maxPage = ceil( listSize / 10 );
	char input[10] = "";
	lists = (char***)malloc( sizeof( char ** ) * nLists );

	va_start( args, postArgs );

	if( showIdx )
		strcat( header, "| Idx\t| ");
	else
		strcat( header, "|\t" );

	for( i = 0; i < nLists; i++ ) {
        lists[i] = va_arg( args, char** );

		strcat( header, va_arg( args, char* ) );
		strcat( header, "|\t\n" );
	}

	while( curPage != -1 ) {

		strcpy( body, "" );
		strcpy( footer, "" );
		for( i = curPage * 10;
			i < listSize && i < ( ( curPage + 1 ) * 10 ) ; i++ )
			{

			if( showIdx )
				sprintf( line, "| %d\t| ", i + 1 );
			else
				strcat( line, "|\t" );

			for( j = 0; j < nLists; j++ ) {
				strcat( line, lists[j][i] );
				strcat( line, " |" );
			}
			strcat( line, "\n" );
			strcat( body, line );

			sprintf( footer, "page %d/%d , %d/%d shown ", curPage+1, maxPage, i + 1, listSize );

		}/*
printf("%s",footer);
		for( j = 0; j < postArgs; j++ ) {
			strcat( footer, " | " );

			strcat( footer, va_arg( args, char* ) );
		}*/
		strcat( footer, "\n(n)ext/(p)revious/(q)uit or page number \n: ");

        printf("%s\n%s\n%s", header, body, footer );
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
			if( ( nPage > 0 ) && ( nPage < maxPage ) )
				curPage = nPage - 1;

        #if _WIN32
            system("cls");
        #else
            system("clear")
        #endif
	}

}
