// type.h
#ifndef TYPE_H
#define TYPE_H

#define NOTYPE 0
#define TYPE_INT 1
#define TYPE_BOOLEAN 2
#define TYPE_VOID 3
#define TYPE_ARRAY 4
#define TYPE_CLASS 5

#define MAX_CLASS_NAME_LENGTH 100

typedef struct {
    int basicType;
    int arrayType;
    char classType[MAX_CLASS_NAME_LENGTH];
} Type;

// Initialisierungen
Type initType(int type);
Type initTypeFull(int type, int arrayType, const char* classType);
Type copyType(const Type* other);

// Funktionen
int equalsType(const Type* t1, const Type* t2);
void typeToString(const Type* t, char* buffer, int bufferSize);

#endif
