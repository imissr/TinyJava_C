#include <symboltable.h>
#include "item.h" // circular dependency issue with item should be called here

/*
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

 
// printf("Alle Items und Typen wurden korrekt freigegeben.\n");*/

static int globalSymbolTableCounter = 10000;

SymbolTable* createSymbolTable(SymbolTable* enclose) {
    SymbolTable* table = malloc(sizeof(SymbolTable));
    table->head = NULL;
    table->last = NULL;
    table->enclose = enclose;
    table->parent = NULL;
    table->no = globalSymbolTableCounter++;
    return table;
}

bool insertItem(SymbolTable* table, Item* object) {
    if (!table) return 0;

    if (table->head == NULL) {
        if (table->parent && table->parent->itemKind == KIND_BLOCK && object->itemKind != KIND_BLOCK) {
            if (getObjectWithKind(table, object->objectName, object->itemKind)) {
                return 0;
            }
        }
        table->head = table->last = object;
        object->parentTable = table;
        return 1;
    }

    Item* temp = table->head;
    while (temp != NULL) {
        if (strcmp(temp->objectName, object->objectName) == 0 &&
            object->itemKind == temp->itemKind &&
            object->itemKind != KIND_BLOCK) {
            return 0;
        }
        temp = temp->next;
    }

    if (table->parent && table->parent->itemKind == KIND_BLOCK) {
        if (getObjectWithKind(table, object->objectName, object->itemKind)) {
            return 0;
        }
    }

    table->last->next = object;
    table->last = object;
    object->parentTable = table;
    return 1;
}

bool deleteItem(SymbolTable* table, const char* name, int kind) {
    if (!table || !table->head) return 0;

    if (table->head->itemKind == kind && strcmp(table->head->objectName, name) == 0) {
        table->head = table->head->next;
        return 1;
    }

    Item* prev = NULL;
    for (Item* temp = table->head; temp != NULL; temp = temp->next) {
        if (temp->itemKind == kind && strcmp(temp->objectName, name) == 0) {
            if (prev) prev->next = temp->next;
            return 1;
        }
        prev = temp;

        if (temp->fields) {
            if (deleteItem(temp->fields, name, kind)) return 1;
        }
    }

    return 0;
}

Item* getObject(SymbolTable* table, const char* name) {
    Item* current = table->head;
    while (current != NULL) {
        if (strcmp(current->objectName, name) == 0) return current;
        current = current->next;
    }

    if (table->enclose) return getObject(table->enclose, name);
    return NULL;
}

Item* getObjectWithKind(SymbolTable* table, const char* name, int kind) {
    Item* current = table->head;
    while (current != NULL) {
        if (strcmp(current->objectName, name) == 0 && current->itemKind == kind) {
            return current;
        }
        current = current->next;
    }

    if (table->enclose) return getObjectWithKind(table->enclose, name, kind);
    return NULL;
}

Item* getParentMethod(SymbolTable* table) {
    if (table->parent->itemKind == KIND_METHOD) return table->parent;
    return getParentMethod(table->parent->parentTable);
}

const char* symbolTableToString(SymbolTable* table, char* buffer, int bufSize) {
    snprintf(buffer, bufSize, "Table %d", table->no - 10000);
    return buffer;
}

void freeSymbolTable(SymbolTable *table, void (*free_item)(Item *)) {
    if (!table)
        return;

    Item *current = table->head;
    while (current) {
        Item *next = current->next;
        if (free_item) {
            free_item(current);
        } else {
            free(current); // falls kein spezieller Freigabe-Code notwendig
        }
        current = next;
    }

    free(table);
}
