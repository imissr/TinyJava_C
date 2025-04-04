#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "linkedlist.h"

// Forward declaration of Item
struct Item;
typedef struct Item Item;

typedef struct SymbolTable {
    Item* head;            // erstes Element
    Item* last;            // letztes Element
    struct SymbolTable* enclose;  // äußere (umgebende) Symboltabelle
    Item* parent;          // übergeordnetes Objekt (z. B. Methode)

    int no;                // für Visualisierung (VCG)
} SymbolTable;

// Konstruktor
SymbolTable* createSymbolTable(SymbolTable* enclose);

// Einfügen, Löschen, Suchen
int insertItem(SymbolTable* table, Item* item);
int deleteItem(SymbolTable* table, const char* name, int kind);
Item* getObject(SymbolTable* table, const char* name);
Item* getObjectWithKind(SymbolTable* table, const char* name, int kind);

// Methoden-Elternelement
Item* getParentMethod(SymbolTable* table);

// Debug
void printSymbolTable(SymbolTable* table);

// Freigabe
void freeSymbolTable(SymbolTable* table);

#endif