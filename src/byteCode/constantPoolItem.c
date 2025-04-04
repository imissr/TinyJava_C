
#include "constantPoolItem.h"
//tested
/*
int main() {
    printf("=== ConstantPoolItem Testing ===\n");

    // UTF8 test
    const char* utf8str = "hello";
    ConstantPoolItem* utf8Item = create_constant_utf8(CONSTANT_UTF8, (const uint8_t*)utf8str, strlen(utf8str));
    printf("UTF8 entry size: %d\n", byte_stream_size(utf8Item));

    // Integer test
    ConstantPoolItem* intItem = create_constant_integer(CONSTANT_INTEGER, 123456);
    printf("Integer entry size: %d\n", byte_stream_size(intItem));

    // Class test
    ConstantPoolItem* classItem = create_constant_class(CONSTANT_CLASS, 2);
    printf("Class entry size: %d\n", byte_stream_size(classItem));

    // Method ref test
    ConstantPoolItem* methodRefItem = create_constant_ref(CONSTANT_METHOD_REF, 5, 10);
    printf("MethodRef entry size: %d\n", byte_stream_size(methodRefItem));

    // Name and type descriptor test
    ConstantPoolItem* nameTypeItem = create_constant_ref(CONSTANT_NAME_TYPE_DESCRIPTOR, 7, 8);
    printf("NameTypeDescriptor entry size: %d\n", byte_stream_size(nameTypeItem));

    // Clean up
    free_constant_pool_item(utf8Item);
    free_constant_pool_item(intItem);
    free_constant_pool_item(classItem);
    free_constant_pool_item(methodRefItem);
    free_constant_pool_item(nameTypeItem);

    printf("=== Done ===\n");
    return 0;
}*/

// Konstruktor: CLASS
ConstantPoolItem* create_constant_class(uint8_t tag, uint16_t index1) {
    ConstantPoolItem* item = (ConstantPoolItem*) calloc(1, sizeof(ConstantPoolItem));
    item->itemTag = tag;
    if (tag == CONSTANT_CLASS) {
        item->itemIndex1 = index1;
    }
    return item;
}

// Konstruktor: INTEGER
ConstantPoolItem* create_constant_integer(uint8_t tag, int32_t value) {
    ConstantPoolItem* item = (ConstantPoolItem*) calloc(1, sizeof(ConstantPoolItem));
    item->itemTag = tag;
    if (tag == CONSTANT_INTEGER) {
        item->itemIntValue = value;
    }
    return item;
}

// Konstruktor: NAME_AND_TYPE, FIELD_REF, METHOD_REF
ConstantPoolItem* create_constant_ref(uint8_t tag, uint16_t index1, uint16_t index2) {
    ConstantPoolItem* item = (ConstantPoolItem*) calloc(1, sizeof(ConstantPoolItem));
    item->itemTag = tag;
    if (tag == CONSTANT_NAME_TYPE_DESCRIPTOR ||
        tag == CONSTANT_FIELD_REF ||
        tag == CONSTANT_METHOD_REF) {
        item->itemIndex1 = index1;
        item->itemIndex2 = index2;
    }
    return item;
}

// Konstruktor: UTF8
ConstantPoolItem* create_constant_utf8(uint8_t tag, const uint8_t* array, uint16_t length) {
    ConstantPoolItem* item = (ConstantPoolItem*) calloc(1, sizeof(ConstantPoolItem));
    item->itemTag = tag;
    if (tag == CONSTANT_UTF8) {
        if (array == NULL || length == 0) {
            item->itemLength = 0;
            item->itemBytes = NULL;
        } else {
            item->itemLength = length;
            item->itemBytes = (uint8_t*) malloc(length);
            memcpy(item->itemBytes, array, length);
        }
    }
    return item;
}

// Methode zur Berechnung der Größe im Byte-Stream
int byte_stream_size(const ConstantPoolItem* item) {
    switch (item->itemTag) {
        case CONSTANT_CLASS:
            return 3;
        case CONSTANT_NAME_TYPE_DESCRIPTOR:
        case CONSTANT_FIELD_REF:
        case CONSTANT_METHOD_REF:
        case CONSTANT_INTEGER:
            return 5;
        case CONSTANT_UTF8:
            return 3 + item->itemLength;
        default:
            return 0;
    }
}


void free_constant_pool_item(ConstantPoolItem* item) {
    if (item != NULL) {
        if (item->itemTag == CONSTANT_UTF8 && item->itemBytes != NULL) {
            free(item->itemBytes);
        }
        free(item);
    }
}