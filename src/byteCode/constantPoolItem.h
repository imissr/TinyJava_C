#ifndef CONSTANT_POOL_H
#define CONSTANT_POOL_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>


// Konstanten-Tags
#define CONSTANT_UTF8                  1
#define CONSTANT_INTEGER               3
#define CONSTANT_CLASS                 7
#define CONSTANT_FIELD_REF             9
#define CONSTANT_METHOD_REF            10
#define CONSTANT_NAME_TYPE_DESCRIPTOR  12

// Die Struktur entspricht der Java-Klasse
typedef struct {
    uint8_t itemTag;         // Tag des konstanten Eintrags

    uint16_t itemIndex1;     // für Methoden, Klassen oder Feldverweise
    uint16_t itemIndex2;     // für Methoden, Klassen oder Feldverweise
    int32_t itemIntValue;    // für INTEGER
    uint16_t itemLength;     // für UTF-8-Einträge
    uint8_t* itemBytes;      // für UTF-8-Einträge
} ConstantPoolItem;


ConstantPoolItem* create_constant_class(uint8_t tag, uint16_t index1);
ConstantPoolItem* create_constant_integer(uint8_t tag, int32_t value);
ConstantPoolItem* create_constant_ref(uint8_t tag, uint16_t index1, uint16_t index2);
ConstantPoolItem* create_constant_utf8(uint8_t tag, const uint8_t* array, uint16_t length);
int byte_stream_size(const ConstantPoolItem* item);
void free_constant_pool_item(ConstantPoolItem* item);

#endif // CONSTANT_POOL_H
