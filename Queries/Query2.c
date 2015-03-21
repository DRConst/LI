#include "Queries.h"


char **query2(ProductCatalog *cat, char t, int *count )
{
	char **toRet = NULL, buff[5];
	int *codes, i, j, used;
	int cnt = 0;

	for (i = 0; i < 26; i++)
	{
		if ( cat->Cat[ t - 'A' ][i] )
		{
			used = cat->Cat[ t - 'A' ][i]->used;
			codes = inOrderBST(cat->Cat[ t - 'A'][i]);
			for (j = 0; j < used; j++)
			{
				toRet = realloc(toRet, sizeof(char*)*(cnt + 1));
				toRet[cnt] = malloc(sizeof(char) * 7);
				toRet[cnt][0] = t;
				toRet[cnt][1] = 'A' + i;
				sprintf( buff, "%d", codes[j] );
				buff[4] = '\0';
				strcpy(toRet[cnt] + 2, buff);
				cnt++;

			}
		}
	}

    *count = cnt;

	return toRet;
}

/*
int main()
{
ProductCatalog *cat;
cat = initProductCatalog(NULL);


char buff[8], b[1024];
FILE *fp;
_getcwd(b, 1024);
fp = fopen("FichProdutos.txt", "r");

while (fgets(buff, 8, fp))
{
cat = insertProduct(cat, buff);
}
query2(cat, 'A');

}*/
