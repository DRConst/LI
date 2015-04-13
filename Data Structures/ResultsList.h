
#pragma once

#include <stdlib.h>
#include <string.h>

typedef struct resultsList *ResultsList;

ResultsList initResultsList();

ResultsList insertResultsList( ResultsList l, char *desc, int value );

int getIdxValueResultsList( ResultsList l, int idx );
int* getValuesResultsList( ResultsList l );

char* getIdxDescResultsList( ResultsList l, int idx );
char** getDescsResultsList( ResultsList l );

int getCountResultsList( ResultsList l );

void freeResultsList( ResultsList l );
