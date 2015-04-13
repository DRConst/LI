#pragma once

#include <stdlib.h>
#include <string.h>

typedef struct stringList *StringList;

StringList initStringList();
StringList insertStringList( StringList l, char *s, int size );

char* getIdxStringList( StringList l, int idx );
char** getStringList( StringList l );

int getCountStringList( StringList l );

void freeStringList( StringList l );
