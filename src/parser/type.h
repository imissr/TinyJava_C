#ifndef TYPE_H
#define TYPE_H

#define MAX_CLASS_NAME_LENGTH 256
#define TYPES_ARRAY_SIZE 6

// Type constants
#define NOTYPE 0
#define TYPE_INT 1
#define TYPE_BOOLEAN 2
#define TYPE_VOID 3
#define TYPE_ARRAY 4
#define TYPE_CLASS 5

typedef struct {
    int basicType;       // object type
    int arrayType;       // array type
    char classType[MAX_CLASS_NAME_LENGTH];  // class type name
    const char* types[TYPES_ARRAY_SIZE];    // Changed to fixed-size array
} Type;  // Added semicolon here

// Function declarations
Type* initType(int type);
Type* copyType(const Type* other);
Type* initTypeFull(int type, int arrayType, const char* classType);
int equalsType(const Type* t1, const Type* t2);
void typeToString(const Type* t, char* buffer, int bufferSize);
void freeType(Type* t);

#endif