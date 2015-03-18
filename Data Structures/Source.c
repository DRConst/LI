#include <stdio.h>
#include <stdlib.h>
#include "ProductCatalog.h"
#include "../Queries/Queries.h"


int main()
{
	/*
	char buff[6];
	FILE *fp;
	fp = fopen("FichClientes.txt", "r");
	
	Sales s = (Sales)malloc(sizeof(struct sales_str));
	s->Tree = (Heap**)malloc(sizeof(Heap*) * 26);
	for (int i = 0; i < 26; i++)
	{
		s->Tree[i] = (Heap*)malloc(sizeof(Heap)*26);
		for (int j = 0; j < 26; j++)
		{
			s->Tree[i][j] = newheap(500);
		}
	}
	int z = 'Z' - 'A';
	while (fgets(buff, 7, fp))
	{
		char b[] = { buff[2], buff[3], buff[4], '\0' };
		int a = atoi(b);
		int i = buff[0] - 'A';
		int j = buff[1] - 'A';
		insertHeap(s->Tree[i][j], a);
	}
	int j;
	while (1)
	{
		extractMin(s->Tree['F' - 'A']['U' - 'A'], &j);
		if (j == 445)
			break;
	}

	ProductCatalog *cat = initProductCatalog(NULL);*/

	ProductCatalog *pCat, *cCat;
	
	char buff[8], b[1024];
	FILE *fp;
	fp = fopen("FichProdutos.txt", "r");


	pCat = initProductCatalog(NULL);
	cCat = initClientCatalog(NULL);

	while (fgets(buff, 8, fp))
	{
		pCat = insertProduct(pCat, buff);
	}

	fp = fopen("FichClientes.txt", "r");

	while (fgets(buff, 8, fp))
	{
		cCat = insertClient(cCat, buff);
	}

	query2(pCat, 'A');
	query6(cCat, 'A');

}


