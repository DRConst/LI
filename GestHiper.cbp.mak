#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.138                       #
#------------------------------------------------------------------------------#


WORKDIR = %cd%

CC = gcc.exe
CXX = g++.exe
AR = ar.exe
LD = g++.exe
WINDRES = windres.exe

INC = 
CFLAGS =  -Wall
RESINC = 
LIBDIR = 
LIB = 
LDFLAGS = 

INC_DEBUG =  $(INC)
CFLAGS_DEBUG =  $(CFLAGS) -pedantic -Wextra -Wall -ansi -g
RESINC_DEBUG =  $(RESINC)
RCFLAGS_DEBUG =  $(RCFLAGS)
LIBDIR_DEBUG =  $(LIBDIR)
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG =  $(LDFLAGS)
OBJDIR_DEBUG = obj\\Debug
DEP_DEBUG = 
OUT_DEBUG = bin\\Debug\\GestHiper.exe

INC_RELEASE =  $(INC)
CFLAGS_RELEASE =  $(CFLAGS) -O2 -pedantic -Wall -ansi
RESINC_RELEASE =  $(RESINC)
RCFLAGS_RELEASE =  $(RCFLAGS)
LIBDIR_RELEASE =  $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE =  $(LDFLAGS)
OBJDIR_RELEASE = obj\\Release
DEP_RELEASE = 
OUT_RELEASE = bin\\Release\\GestHiper.exe

OBJ_DEBUG = $(OBJDIR_DEBUG)\\src\\GestHiper.o $(OBJDIR_DEBUG)\\src\\Data\ Structures\\minHeap.o $(OBJDIR_DEBUG)\\src\\Data\ Structures\\StringList.o $(OBJDIR_DEBUG)\\src\\Data\ Structures\\Sales.o $(OBJDIR_DEBUG)\\src\\Data\ Structures\\Sale.o $(OBJDIR_DEBUG)\\src\\Data\ Structures\\ResultsList.o $(OBJDIR_DEBUG)\\src\\Data\ Structures\\ProductCatalog.o $(OBJDIR_DEBUG)\\src\\Data\ Structures\\HashTable.o $(OBJDIR_DEBUG)\\src\\Data\ Structures\\ClientCatalog.o $(OBJDIR_DEBUG)\\src\\Data\ Structures\\BST.o $(OBJDIR_DEBUG)\\src\\Data\ Structures\\Accounting.o

OBJ_RELEASE = $(OBJDIR_RELEASE)\\src\\GestHiper.o $(OBJDIR_RELEASE)\\src\\Data\ Structures\\minHeap.o $(OBJDIR_RELEASE)\\src\\Data\ Structures\\StringList.o $(OBJDIR_RELEASE)\\src\\Data\ Structures\\Sales.o $(OBJDIR_RELEASE)\\src\\Data\ Structures\\Sale.o $(OBJDIR_RELEASE)\\src\\Data\ Structures\\ResultsList.o $(OBJDIR_RELEASE)\\src\\Data\ Structures\\ProductCatalog.o $(OBJDIR_RELEASE)\\src\\Data\ Structures\\HashTable.o $(OBJDIR_RELEASE)\\src\\Data\ Structures\\ClientCatalog.o $(OBJDIR_RELEASE)\\src\\Data\ Structures\\BST.o $(OBJDIR_RELEASE)\\src\\Data\ Structures\\Accounting.o

all: debug release

clean: clean_debug clean_release

before_debug: 
	cmd /c if not exist bin\\Debug md bin\\Debug
	cmd /c if not exist $(OBJDIR_DEBUG)\\src md $(OBJDIR_DEBUG)\\src
	cmd /c if not exist $(OBJDIR_DEBUG)\\src\\Data\ Structures md $(OBJDIR_DEBUG)\\src\\Data\ Structures

after_debug: 

debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LIBDIR_DEBUG) -o $(OUT_DEBUG) $(OBJ_DEBUG)  $(LDFLAGS_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)\\src\\GestHiper.o: src\\GestHiper.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src\\GestHiper.c -o $(OBJDIR_DEBUG)\\src\\GestHiper.o

$(OBJDIR_DEBUG)\\src\\Data\ Structures\\minHeap.o: src\\Data\ Structures\\minHeap.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src\\Data\ Structures\\minHeap.c -o $(OBJDIR_DEBUG)\\src\\Data\ Structures\\minHeap.o

$(OBJDIR_DEBUG)\\src\\Data\ Structures\\StringList.o: src\\Data\ Structures\\StringList.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src\\Data\ Structures\\StringList.c -o $(OBJDIR_DEBUG)\\src\\Data\ Structures\\StringList.o

$(OBJDIR_DEBUG)\\src\\Data\ Structures\\Sales.o: src\\Data\ Structures\\Sales.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src\\Data\ Structures\\Sales.c -o $(OBJDIR_DEBUG)\\src\\Data\ Structures\\Sales.o

$(OBJDIR_DEBUG)\\src\\Data\ Structures\\Sale.o: src\\Data\ Structures\\Sale.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src\\Data\ Structures\\Sale.c -o $(OBJDIR_DEBUG)\\src\\Data\ Structures\\Sale.o

$(OBJDIR_DEBUG)\\src\\Data\ Structures\\ResultsList.o: src\\Data\ Structures\\ResultsList.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src\\Data\ Structures\\ResultsList.c -o $(OBJDIR_DEBUG)\\src\\Data\ Structures\\ResultsList.o

$(OBJDIR_DEBUG)\\src\\Data\ Structures\\ProductCatalog.o: src\\Data\ Structures\\ProductCatalog.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src\\Data\ Structures\\ProductCatalog.c -o $(OBJDIR_DEBUG)\\src\\Data\ Structures\\ProductCatalog.o

$(OBJDIR_DEBUG)\\src\\Data\ Structures\\HashTable.o: src\\Data\ Structures\\HashTable.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src\\Data\ Structures\\HashTable.c -o $(OBJDIR_DEBUG)\\src\\Data\ Structures\\HashTable.o

$(OBJDIR_DEBUG)\\src\\Data\ Structures\\ClientCatalog.o: src\\Data\ Structures\\ClientCatalog.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src\\Data\ Structures\\ClientCatalog.c -o $(OBJDIR_DEBUG)\\src\\Data\ Structures\\ClientCatalog.o

$(OBJDIR_DEBUG)\\src\\Data\ Structures\\BST.o: src\\Data\ Structures\\BST.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src\\Data\ Structures\\BST.c -o $(OBJDIR_DEBUG)\\src\\Data\ Structures\\BST.o

$(OBJDIR_DEBUG)\\src\\Data\ Structures\\Accounting.o: src\\Data\ Structures\\Accounting.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src\\Data\ Structures\\Accounting.c -o $(OBJDIR_DEBUG)\\src\\Data\ Structures\\Accounting.o

clean_debug: 
	cmd /c del /f $(OBJ_DEBUG) $(OUT_DEBUG)
	cmd /c rd bin\\Debug
	cmd /c rd $(OBJDIR_DEBUG)\\src
	cmd /c rd $(OBJDIR_DEBUG)\\src\\Data\ Structures

before_release: 
	cmd /c if not exist bin\\Release md bin\\Release
	cmd /c if not exist $(OBJDIR_RELEASE)\\src md $(OBJDIR_RELEASE)\\src
	cmd /c if not exist $(OBJDIR_RELEASE)\\src\\Data\ Structures md $(OBJDIR_RELEASE)\\src\\Data\ Structures

after_release: 

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE)  $(LDFLAGS_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)\\src\\GestHiper.o: src\\GestHiper.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\GestHiper.c -o $(OBJDIR_RELEASE)\\src\\GestHiper.o

$(OBJDIR_RELEASE)\\src\\Data\ Structures\\minHeap.o: src\\Data\ Structures\\minHeap.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\Data\ Structures\\minHeap.c -o $(OBJDIR_RELEASE)\\src\\Data\ Structures\\minHeap.o

$(OBJDIR_RELEASE)\\src\\Data\ Structures\\StringList.o: src\\Data\ Structures\\StringList.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\Data\ Structures\\StringList.c -o $(OBJDIR_RELEASE)\\src\\Data\ Structures\\StringList.o

$(OBJDIR_RELEASE)\\src\\Data\ Structures\\Sales.o: src\\Data\ Structures\\Sales.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\Data\ Structures\\Sales.c -o $(OBJDIR_RELEASE)\\src\\Data\ Structures\\Sales.o

$(OBJDIR_RELEASE)\\src\\Data\ Structures\\Sale.o: src\\Data\ Structures\\Sale.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\Data\ Structures\\Sale.c -o $(OBJDIR_RELEASE)\\src\\Data\ Structures\\Sale.o

$(OBJDIR_RELEASE)\\src\\Data\ Structures\\ResultsList.o: src\\Data\ Structures\\ResultsList.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\Data\ Structures\\ResultsList.c -o $(OBJDIR_RELEASE)\\src\\Data\ Structures\\ResultsList.o

$(OBJDIR_RELEASE)\\src\\Data\ Structures\\ProductCatalog.o: src\\Data\ Structures\\ProductCatalog.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\Data\ Structures\\ProductCatalog.c -o $(OBJDIR_RELEASE)\\src\\Data\ Structures\\ProductCatalog.o

$(OBJDIR_RELEASE)\\src\\Data\ Structures\\HashTable.o: src\\Data\ Structures\\HashTable.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\Data\ Structures\\HashTable.c -o $(OBJDIR_RELEASE)\\src\\Data\ Structures\\HashTable.o

$(OBJDIR_RELEASE)\\src\\Data\ Structures\\ClientCatalog.o: src\\Data\ Structures\\ClientCatalog.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\Data\ Structures\\ClientCatalog.c -o $(OBJDIR_RELEASE)\\src\\Data\ Structures\\ClientCatalog.o

$(OBJDIR_RELEASE)\\src\\Data\ Structures\\BST.o: src\\Data\ Structures\\BST.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\Data\ Structures\\BST.c -o $(OBJDIR_RELEASE)\\src\\Data\ Structures\\BST.o

$(OBJDIR_RELEASE)\\src\\Data\ Structures\\Accounting.o: src\\Data\ Structures\\Accounting.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\Data\ Structures\\Accounting.c -o $(OBJDIR_RELEASE)\\src\\Data\ Structures\\Accounting.o

clean_release: 
	cmd /c del /f $(OBJ_RELEASE) $(OUT_RELEASE)
	cmd /c rd bin\\Release
	cmd /c rd $(OBJDIR_RELEASE)\\src
	cmd /c rd $(OBJDIR_RELEASE)\\src\\Data\ Structures

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release

