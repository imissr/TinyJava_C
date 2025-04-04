#include "item.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symboltable.h"

static int globalItemCounter = 0;

Item* createItem() {
    return createItemFull(NULL, NOKIND, NOSUBKIND, initType(TYPE_VOID), 0, 0, NULL);
}

Item* createItemWithType(Type* type) {
    return createItemFull(NULL, NOKIND, NOSUBKIND, type, 0, 0, NULL);
}

Item* createItemFrom(Item* other) {
    return createItemFull(
        other->objectName ? strdup(other->objectName) : NULL,
        other->itemKind,
        other->itemSubkind,
        copyType(other->objectType),
        other->staticModifier,
        other->finalModifier,
        other->next
    );
}

Item* createItemFull(const char* name, int kind, int subkind, Type* type, int isStatic, int isFinal, Item* next) {
    Item* item = malloc(sizeof(Item));
    item->objectName = name ? strdup(name) : NULL;
    item->itemKind = kind;
    item->itemSubkind = subkind;
    item->objectType = type;
    item->staticModifier = isStatic;
    item->finalModifier = isFinal;
    item->next = next;
    item->fields = NULL;
    item->parentTable = NULL;
    item->constantPoolIndex = -1;
    item->mark = 0;
    item->isInitialized = 0;
    item->no = globalItemCounter++;
    return item;
}

/*short createConstantPoolItem(Item* item, LinkedList* constantPool) {
    char desc[512];
    uint8_t* nameBytes;
    short index1 = 0, index2 = 0, index3 = 0;

    if (!item || !item->objectName) return -1;

    switch (item->itemKind) {
        case KIND_CLASS:
            nameBytes = (uint8_t*)strdup(item->objectName);
            linkedlist_append(constantPool, create_constant_utf8(CONSTANT_UTF8, nameBytes, strlen((char*)nameBytes)));
            index1 = (short)(linkedlist_size(constantPool) - 1);
            linkedlist_append(constantPool, create_constant_class(CONSTANT_CLASS, index1));
            item->constantPoolIndex = (short)(linkedlist_size(constantPool) - 1);
            break;

        case KIND_VAR:
            nameBytes = (uint8_t*)strdup(item->objectName);
            linkedlist_append(constantPool, create_constant_utf8(CONSTANT_UTF8, nameBytes, strlen((char*)nameBytes)));
            index1 = (short)(linkedlist_size(constantPool) - 1);
            snprintf(desc, sizeof(desc), "%s", getDescriptor(item));
            linkedlist_append(constantPool, create_constant_utf8(CONSTANT_UTF8, (uint8_t*)desc, strlen(desc)));
            index2 = (short)(linkedlist_size(constantPool) - 1);
            linkedlist_append(constantPool, create_constant_ref(CONSTANT_NAME_TYPE_DESCRIPTOR, index1, index2));
            index3 = (short)(linkedlist_size(constantPool) - 1);
            linkedlist_append(constantPool, create_constant_ref(CONSTANT_FIELD_REF, getParent(item)->constantPoolIndex, index3));
            item->constantPoolIndex = (short)(linkedlist_size(constantPool) - 1);
            break;

        case KIND_METHOD: {
            nameBytes = (uint8_t*)strdup(item->objectName);
            linkedlist_append(constantPool, create_constant_utf8(CONSTANT_UTF8, nameBytes, strlen((char*)nameBytes)));
            index1 = (short)(linkedlist_size(constantPool) - 1);

            strcpy(desc, "(");
            if (item->fields) {
                for (LinkedListNode* node = item->fields->head; node; node = node->next) {
                    Item* attr = (Item*)node->data;
                    if (attr->itemSubkind == SUBKIND_PARAM) {
                        strcat(desc, getDescriptor(attr));
                    }
                }
            }
            strcat(desc, ")");
            strcat(desc, item->objectType->basicType == TYPE_VOID ? "V" : "I");

            linkedlist_append(constantPool, create_constant_utf8(CONSTANT_UTF8, (uint8_t*)desc, strlen(desc)));
            index2 = (short)(linkedlist_size(constantPool) - 1);
            linkedlist_append(constantPool, create_constant_ref(CONSTANT_NAME_TYPE_DESCRIPTOR, index1, index2));
            index3 = (short)(linkedlist_size(constantPool) - 1);
            
            short parentIndex = getParent(item)->constantPoolIndex;
            linkedlist_append(constantPool, create_constant_ref(CONSTANT_METHOD_REF, parentIndex, index3));
            item->constantPoolIndex = (short)(linkedlist_size(constantPool) - 1);
            break;
        }
    }

    return item->constantPoolIndex;
}*/


const char* getDescriptor(Item* item) {
    if (!item || !item->objectType) return "";
    switch (item->objectType->basicType) {
        case TYPE_INT: return "I";
        case TYPE_ARRAY: return "[I";
        case TYPE_CLASS: {
            static char classDesc[512];
            snprintf(classDesc, sizeof(classDesc), "L%s;", item->objectType->classType);
            return classDesc;
        }
        default: return "";
    }
}

Item* getParent(Item* item) {
    if (!item || !item->parentTable || !item->parentTable->parent) return NULL;
    if (item->parentTable->parent->itemKind == KIND_BLOCK)
        return getParent(item->parentTable->parent);
    return item->parentTable->parent;
}

void itemToString(Item* item, char* buffer, int bufferSize) {
    if (!item || !buffer || bufferSize <= 0) return;
    char typeBuf[256];
    typeToString(item->objectType, typeBuf, sizeof(typeBuf));
    snprintf(buffer, bufferSize, "%s\n%s\n%s\n%s\n%s\n%s",
        item->itemKind == NOKIND ? "-" : (item->itemKind == KIND_CLASS ? "CLASS" : item->itemKind == KIND_METHOD ? "METHOD" : item->itemKind == KIND_VAR ? "VAR" : "BLOCK"),
        item->itemSubkind == NOSUBKIND ? "-" : (item->itemSubkind == SUBKIND_CONSTR ? "CONSTR" : "PARAM"),
        typeBuf,
        item->objectName ? item->objectName : "-",
        item->finalModifier ? "final" : "-",
        item->staticModifier ? "static" : "-"
    );
}

void freeItem(Item* item) {
    if (!item) return;

    // Free the object name if it exists
    if (item->objectName) {
        free(item->objectName);
        item->objectName = NULL;
    }

    // Free the object type if it exists
    if (item->objectType) {
        freeType(item->objectType);
        item->objectType = NULL;
    }

    // Free the item itself
    free(item);
}