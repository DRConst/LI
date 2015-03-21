#pragma once

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "./Data Structures/ProductCatalog.h"
#include "./Data Structures/ClientCatalog.h"
#include "./Queries/Queries.h"

#define MAX_PATH 150

#define PER_PAGE 15

#define MAX_SEPARATOR "------------------------------------------------------------------------------------------------------------------"

#define HEADER_MENU "\n-------------------------------------------------------------\n"
#define MENU_OPTION_1 " 1\t-\tRead Files\n"
#define MENU_OPTION_2 " 2\t-\tProducts By Prefix\n"
#define MENU_OPTION_3 " 3\t-\tProduct Sales Info(given month)\n"
#define MENU_OPTION_4 " 4 \t-\tUnbought Products\n"
#define MENU_OPTION_5 " 5 \t-\tClient's Sales History\n"
#define MENU_OPTION_6 " 6 \t-\tClients By Prefix\n"
#define MENU_OPTION_7 " 7 \t-\tSales Info (month interval)\n"
#define MENU_OPTION_8 " 8 \t-\tList Product Buyers\n"
#define MENU_OPTION_9 " 9 \t-\tClient's Detailed Sales History(given month)\n"
#define MENU_OPTION_10 " 10\t-\tList Active Clients\n"
#define MENU_OPTION_11 " 11\t-\tGenerate CSV\n"
#define MENU_OPTION_12 " 12\t-\tMost Wanted\n"
#define MENU_OPTION_13 " 13\t-\tClient's Top 3 Most Bought\n"
#define MENU_OPTION_14 " 14\t-\tInactive Clients And Products\n"
#define EXIT_OPTION " 0\t-\tExit Program\n"

void paginateResults( int a, int b, int c, int d, ... );
