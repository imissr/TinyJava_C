#ifndef DUMMY_METHOD_H
#define DUMMY_METHOD_H

#include "node.h"

typedef struct DummyMethod {
    char* name;
    Node* node;
    Node* paramNode;
} DummyMethod;

// Constructor
DummyMethod* createDummyMethod(const char* name, Node* node, Node* paramNode);

// Destructor
void freeDummyMethod(DummyMethod* method);

#endif