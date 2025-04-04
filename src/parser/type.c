#include "type.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* tested und zero memory leaks
int main() {
    // Typen initialisieren
    Type *t1 = initType(TYPE_INT);
    Type *t2 = initTypeFull(TYPE_CLASS, NOTYPE, "MyClass");
    Type *t3 = copyType(t2);
    Type *t4 = initTypeFull(TYPE_ARRAY, TYPE_BOOLEAN, "");

    // Buffer zur Darstellung
    char buffer[256];

    // Typ 1 anzeigen
    typeToString(t1, buffer, sizeof(buffer));
    printf("Type 1:\n%s\n", buffer);

    // Typ 2 anzeigen
    typeToString(t2, buffer, sizeof(buffer));
    printf("Type 2:\n%s\n", buffer);

    // Typ 3 anzeigen (Kopie von Typ 2)
    typeToString(t3, buffer, sizeof(buffer));
    printf("Type 3 (copy of Type 2):\n%s\n", buffer);

    // Typ 4 anzeigen (Array von BOOLEAN)
    typeToString(t4, buffer, sizeof(buffer));
    printf("Type 4:\n%s\n", buffer);

    // Typvergleich
    printf("t2 == t3? %s\n", equalsType(t2, t3) ? "Yes" : "No");
    printf("t1 == t4? %s\n", equalsType(t1, t4) ? "Yes" : "No");

    // Alle Typen freigeben
    freeType(t1);
    freeType(t2);
    freeType(t3);
    freeType(t4);

    return 0;
}
*/

Type *initType(int type)
{
    return initTypeFull(type, NOTYPE, "");
}

Type *copyType(const Type *other)
{
    return initTypeFull(other->basicType, other->arrayType, other->classType);
}

Type *initTypeFull(int type, int arrayType, const char *classType)
{
    Type *t = malloc(sizeof(Type));
    if (t == NULL)
    {
        return NULL;
    }
    t->basicType = type;
    t->arrayType = arrayType;
    strncpy(t->classType, classType ? classType : "", MAX_CLASS_NAME_LENGTH - 1);
    t->classType[MAX_CLASS_NAME_LENGTH - 1] = '\0';

    t->types[0] = "NOTYPE";
    t->types[1] = "INT";
    t->types[2] = "BOOLEAN";
    t->types[3] = "VOID";
    t->types[4] = "ARRAY";
    t->types[5] = "CLASS";

    return t;
}

int equalsType(const Type *t1, const Type *t2)
{
    if (!t1 || !t2)
        return 0;

    if (t1->basicType == TYPE_INT || t1->basicType == TYPE_BOOLEAN || t1->basicType == TYPE_VOID)
    {
        return t1->basicType == t2->basicType;
    }
    if (t1->basicType == TYPE_ARRAY && t2->basicType == TYPE_ARRAY)
    {
        return t1->arrayType == t2->arrayType;
    }
    if (t1->basicType == TYPE_CLASS && t2->basicType == TYPE_CLASS)
    {
        return strcmp(t1->classType, t2->classType) == 0;
    }
    return 0;
}

void typeToString(const Type *t, char *buffer, int bufferSize)
{
    if (!t || !buffer || bufferSize <= 0)
        return;

    snprintf(buffer, bufferSize, "%s\n%s",
             t->types[t->basicType],
             (t->basicType == TYPE_CLASS) ? t->classType : (t->basicType == TYPE_ARRAY) ? t->types[t->arrayType]
                                                                                        : "-");
}

void freeType(Type *t)
{


    free(t);
}