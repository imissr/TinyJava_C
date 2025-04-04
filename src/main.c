#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
#include "constantPoolItem.h"





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
}
