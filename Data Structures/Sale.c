#include "Sale.h"

typedef struct sale
{
	int month, amnt;
	double price;
	char *product, *client, type;
}*Sale_s;


Sale_s createSale(int month, int amnt, double price, char *product, char *client, char type)
{
	Sale_s s = malloc(sizeof(*s));
	if (!s)
		return NULL;
	s->amnt = amnt;
	s->month = month;
	s->price = price;
	s->type = type;
	s->product = malloc(sizeof(char) * 70);
	strcpy(s->product, product);
	s->client = malloc(sizeof(char) * 60);
	strcpy(s->client, client);
	return s;
}


int copySale(Sale_s *dest, Sale_s src)
{

	if (dest == NULL)
		return 0;

	*dest = createSale(src->month, src->amnt, src->price, src->product, src->client, src->type);

	return !(*dest == NULL);
}

/* Gets */

int getSaleMonth( Sale_s s )
{
    return !s ? -1 : s->month;
}

int getSaleQtd( Sale_s s )
{
    return !s ? -1 : s->amnt;
}

double getSalePrice( Sale_s s )
{
    return !s ? (double)-1 : s->price;
}

char* getSaleProduct( Sale_s s )
{
    return !s ? NULL : s->product;
}

char* getSaleClient( Sale_s s )
{
    return !s ? NULL : s->client;
}

char getSaleType( Sale_s s )
{
    return !s ? '-' : s->type;
}


void freeSale( Sale_s s )
{
    free( s );
}
