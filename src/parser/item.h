#ifndef ITEM_H
#define ITEM_H

#include "type.h"
#include "constantPoolItem.h"
#include "linkedlist.h"
#include "symboltable.h"

// Item-Kinds
#define NOKIND 0
#define KIND_CLASS 1
#define KIND_METHOD 2
#define KIND_VAR 3
#define KIND_BLOCK 4

// Item-Subkinds
#define NOSUBKIND 0
#define SUBKIND_CONSTR 1
#define SUBKIND_PARAM 2

// Struktur Item
typedef struct Item
{
    int itemKind;
    int itemSubkind;

    char *objectName;
    Type *objectType;

    int staticModifier;
    int finalModifier;

    struct Item *next;
    SymbolTable *fields;
    SymbolTable *parentTable;

    short constantPoolIndex;
    int mark;

    int no;
    int isInitialized;
} Item;

Item *createItem();
Item *createItemWithType(Type *type);
Item *createItemFrom(Item *other);
Item *createItemFull(const char *name, int kind, int subkind, Type *type, int isStatic, int isFinal, Item *next);

short createConstantPoolItem(Item *item, LinkedList *constantPool);
const char *getDescriptor(Item *item);
Item *getParent(Item *item);
void itemToString(Item *item, char *buffer, int bufferSize);
void freeItem(Item *item);

#endif
