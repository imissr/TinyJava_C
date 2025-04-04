#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>


// Forward Declaration
struct Item;
typedef struct Item Item;
typedef struct SymbolTable
{
    Item *head;
    Item *last;
    struct SymbolTable *enclose;
    Item *parent;
    int no;
} SymbolTable;

SymbolTable *createSymbolTable(SymbolTable *enclose);

bool insertItem(SymbolTable *table, Item *object);

bool deleteItem(SymbolTable *table, const char *name, int kind);

Item *getObject(SymbolTable *table, const char *name);

Item *getObjectWithKind(SymbolTable *table, const char *name, int kind);

Item *getParentMethod(SymbolTable *table);

const char *symbolTableToString(SymbolTable *table, char *buffer, int bufSize);

void freeSymbolTable(SymbolTable *table, void (*free_item)(Item *));

#endif
