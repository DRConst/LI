#pragma once
#include <stdlib.h>
#include <string.h>

typedef struct sale *Sale;

Sale createSale(int month, int amnt, double price, char *product, char *client, char type);
int copySale(Sale *dest, Sale src);
void freeSale( Sale s );


/* Gets */
int getSaleMonth( Sale s );

int getSaleQtd( Sale s );

double getSalePrice( Sale s );

char* getSaleProduct( Sale s );

char* getSaleClient( Sale s );

char getSaleType( Sale s );
