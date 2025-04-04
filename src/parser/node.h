#ifndef NODE_H
#define NODE_H

#include "item.h"
#include <stdbool.h>
#include <stdlib.h>

// Node Klassen (nodeClass)
#define NOCLASS 0
#define CLASS_VAR 1
#define CLASS_CONST 2
#define CLASS_BINOP 3
#define CLASS_SELECT_INDEX 4
#define CLASS_WHILE 5
#define CLASS_IF 6
#define CLASS_IFELSE 7
#define CLASS_ASSIGN 8
#define CLASS_SELECT_MEMBER 9
#define CLASS_CALL 10
#define CLASS_ENTER 11
#define CLASS_CLASS 12
#define CLASS_RETURN 13
#define CLASS_NEW 14
#define CLASS_METHOD 15
#define CLASS_ARRAYLENGTH 16

// Node Subklassen (nodeSubclass)
#define NOSUBCLASS 0
#define SUBCLASS_TIMES 1
#define SUBCLASS_DIV 2
#define SUBCLASS_PLUS 3
#define SUBCLASS_EQ 4
#define SUBCLASS_LT 5
#define SUBCLASS_GT 6
#define SUBCLASS_LEQ 7
#define SUBCLASS_GEQ 8
#define SUBCLASS_MINUS 9
#define SUBCLASS_UNEQUAL 10

extern const char *kinds[];
extern const char *subkinds[];

// Node-Struktur
typedef struct Node
{
    int nodeClass;
    int nodeSubclass;
    Item *nodeObject;

    struct Node *left;
    struct Node *right;
    struct Node *parent;
    struct Node *next;
    struct Node *prev;

    int constIntValue;
    int no;
} Node;

// Konstruktorfunktionen
Node *createNode(); // Standard

Node *createNodeFrom(Node *other); // Copy

Node *createNodeWithClass(int kind); // Nur nodeClass

Node *createNodeFull(int kind, int subkind, Item *object,
                     Node *left, Node *right, Node *parent, Node *next);
Node *createNodeWithConst(int kind, int subkind, Item *object,
                          Node *l, Node *r, Node *p, Node *n, int intValue);

void attachNode(Node *base, Node *node);

Node *concatNodes(Node *first, Node *second);

void deleteNode(Node *node);

// ...existing code...
void nodeToString(const Node *node, char *buffer, size_t bufferSize);

bool returnMethodVisitor(const Node *node);

bool staticMethodVisitor(const Node *node);

// Speicherfreigabe
void freeNode(Node *node);

#endif // NODE_H
