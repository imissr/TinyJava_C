#include "type.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//tested
/*
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
}*/
const char* types[] = { "NOTYPE", "INT", "BOOLEAN", "VOID", "ARRAY", "CLASS" };

Type* initType(int type) {
    return initTypeFull(type, NOTYPE, "");
}

Type* copyType(const Type* other) {
    return initTypeFull(other->basicType, other->arrayType, other->classType);
}

Type* initTypeFull(int type, int arrayType, const char* classType) {
    Type* t = malloc(sizeof(Type));
    if (t == NULL) {
        return NULL;
    }
    t->basicType = type;
    t->arrayType = arrayType;
    strncpy(t->classType, classType ? classType : "", MAX_CLASS_NAME_LENGTH - 1);
    t->classType[MAX_CLASS_NAME_LENGTH - 1] = '\0';
    return t;
}

int equalsType(const Type* t1, const Type* t2) {
    if (!t1 || !t2) return 0;
    
    if (t1->basicType == TYPE_INT || t1->basicType == TYPE_BOOLEAN || t1->basicType == TYPE_VOID) {
        return t1->basicType == t2->basicType;
    }
    if (t1->basicType == TYPE_ARRAY && t2->basicType == TYPE_ARRAY) {
        return t1->arrayType == t2->arrayType;
    }
    if (t1->basicType == TYPE_CLASS && t2->basicType == TYPE_CLASS) {
        return strcmp(t1->classType, t2->classType) == 0;
    }
    return 0;
}

void typeToString(const Type* t, char* buffer, int bufferSize) {
    if (!t || !buffer || bufferSize <= 0) return;
    
    snprintf(buffer, bufferSize, "%s\n%s",
             types[t->basicType],
             (t->basicType == TYPE_CLASS) ? t->classType :
             (t->basicType == TYPE_ARRAY) ? types[t->arrayType] : "-");
}

void freeType(Type* t) {
    free(t);
}