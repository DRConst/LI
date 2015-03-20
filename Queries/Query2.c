#include "Queries.h"


char **query2(ProductCatalog *cat, char t, int *count )
{
	char **toRet = NULL, buff[5];
	int *codes, i, j, used;
	int cnt = 0;
	for (i = 0; i < 26; i++)
	{
		if (cat->Cat['A' - toupper(t)][i])
		{
			used = cat->Cat['A' - toupper(t)][i]->used;
			codes = inOrderBST(cat->Cat['A' - toupper(t)][i]);
			for (j = 0; j < used; j++)
			{
				toRet = realloc(toRet, sizeof(char*)*(cnt + 1));
				toRet[cnt] = malloc(sizeof(char) * 7);
				toRet[cnt][0] = t;
				toRet[cnt][1] = 'A' + i;
				itoa(codes[j], buff, 10);
				buff[4] = '\0';
				strcpy(toRet[cnt] + 2, buff);
				cnt++;

			}
		}
	}

    *count = cnt;
/*
    paginateResults( 1, cnt, 1, 1, toRet, "Produtos", cnt );
    /*
	for (i = 0; i < cnt; i++)
	{
		printf("%s\n", toRet[i]);
	}
	*/
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
