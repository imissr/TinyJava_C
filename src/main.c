#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include "type.h"
#include "symboltable.h"

int main() {
    // Erstelle Typen
    Type *t1 = initType(TYPE_INT);
    Type *t2 = initTypeFull(TYPE_CLASS, NOTYPE, "MyClass");
    
    const char *name = "x";
    const char *name2 = "y";
    // Erstelle Items
    Item *i1 = createItemFull(name, KIND_VAR, NOSUBKIND, copyType(t1), 0, 0, NULL);
    Item *i2 = createItemFull(name2, KIND_VAR, NOSUBKIND, copyType(t2), 1, 1, NULL);

    // Erstelle Symboltabelle
  SymbolTable *table = createSymbolTable(NULL);
    insertItem(table, i1);
    insertItem(table, i2);

    // Erstelle verschachtelte Item mit Feldern
    Item *method = createItemFull("doSomething", KIND_METHOD, NOSUBKIND, initType(TYPE_VOID), 0, 0, NULL);
    method->fields = createSymbolTable(NULL);
    insertItem(method->fields, createItemFull("param1", KIND_VAR, SUBKIND_PARAM, initType(TYPE_INT), 0, 0, NULL));

    insertItem(table, method);

    // Gib alles frei
    freeSymbolTable(table, freeItem);
    freeType(t1);
    freeType(t2);
    //no need because freeSymbolTable will free the items
   /* freeItem(i1);
    freeItem(i2);*/

 
    printf("Alle Items und Typen wurden korrekt freigegeben.\n");
    return 0;
}
