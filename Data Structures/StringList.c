#include "StringList.h"

typedef struct stringList
{
    char **data;
    int *size;
    int count;
}*StringList_s;


StringList_s initStringList()
{
    StringList_s toRet = (StringList_s)malloc( sizeof( struct stringList ));


    toRet->data = (char**)malloc( sizeof(char**) );
    toRet->count = 0;
    toRet->size = (int*)malloc( sizeof(int) );


    return toRet;
}


StringList_s insertStringList( StringList_s l, char *s, int len )
{
    int count;


    if( !l)
        return NULL;

    count = l->count;

    l->size = (int*)realloc( l->size, sizeof(int)*(count + 1) );
    l->data = (char**)realloc( l->data, sizeof(char*)*(count + 1) );

    l->size[ count ] = len;
    l->data[ count ] = (char*)malloc( len + 1 );

    strcpy( l->data[count], s );

    l->count++;

    return l;
}


char* getIdxStringList( StringList_s l, int idx )
{

    if( !l || (idx >= l->count) )
        return NULL;

    return l->data[ idx ];
}

char** getStringList( StringList_s l )
{
    if(!l || l->count == 0)
        return NULL;

    return l->data;
}

int getCountStringList( StringList_s l )
{
    return (!l) ? 0 : l->count;
}


void freeStringList( StringList_s l )
{
    int i;

    if( !l )
        return;

    for( i = 0; i < l->count; i++ )
        free( l->data[i] );

    free( l->data );
    free( l->size );

    free( l );
}
