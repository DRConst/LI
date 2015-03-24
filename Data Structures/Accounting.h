#pragma once

typedef struct sale
{
	int month, amnt;
	float price;
	char *product, *client, type;
}Sale;

typedef struct entry
{
	int *cnt;
	int units;
	int **records; //Matrix Month x Index
}Entry;


typedef struct accounting
{
	int cntE, cntS;
	Entry *entries;
	Sale *sales;
}Accounting;



