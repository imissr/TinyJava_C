#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
#include "type.h"



int main() {
    Type *t1 = initType(TYPE_INT);
    Type *t2 = initTypeFull(TYPE_CLASS, NOTYPE, "MyClass");

    char buffer[256];
    typeToString(t1, buffer, sizeof(buffer));
    printf("Type 1:\n%s\n", buffer);

    typeToString(t2, buffer, sizeof(buffer));
    printf("Type 2:\n%s\n", buffer);

    printf("Types equal? %s\n", equalsType(t1, t2) ? "Yes" : "No");

    return 0;
}
