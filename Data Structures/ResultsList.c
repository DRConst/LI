#include "ResultsList.h"

typedef struct resultsList
{
    char **desc;
    int *data;
    int count;
}*ResultsList_s;


ResultsList_s initResultsList()
{
    ResultsList_s toRet = (ResultsList_s)malloc( sizeof( struct resultsList ));


    toRet->desc = (char**)malloc( sizeof(char**) );
    toRet->count = 0;
    toRet->data = (int*)malloc( sizeof(int) );


    return toRet;
}


ResultsList_s insertResultsList( ResultsList_s l, char *desc, int value )
{
    int count;


    if( !l)
        return NULL;

    count = l->count;

    l->data = (int*)realloc( l->data, sizeof(int)*(count + 1) );
    l->desc = (char**)realloc( l->desc, sizeof(char*)*(count + 1) );

    l->data[ count ] = value;
    l->desc[ count ] = (char*)malloc( strlen( desc ) + 1 );

    strcpy( l->desc[count], desc );

    l->count++;

    return l;
}

int getIdxValueResultsList( ResultsList_s l, int idx )
{
    if( !l || (idx >= l->count) )
        return -1;

    return l->data[idx];
}

int* getValuesResultsList( ResultsList_s l )
{
    if( !l )
        return NULL;

    return l->data;
}

char* getIdxDescResultsList( ResultsList_s l, int idx )
{

    if( !l || (idx >= l->count) )
        return NULL;

    return l->desc[ idx ];
}

char** getDescsResultsList( ResultsList_s l )
{
    if(!l)
        return NULL;

    return l->desc;
}

int getCountResultsList( ResultsList_s l )
{
    return (!l) ? 0 : l->count;
}


void freeResultsList( ResultsList_s l )
{
    int i;

    if( !l )
        return;

    for( i = 0; i < l->count; i++ )
        free( l->desc[i] );

    free( l->desc );
    free( l->data );

    free( l );
}
