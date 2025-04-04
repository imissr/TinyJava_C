#include "dummyMethod.h"
#include <stdlib.h>
#include <string.h>

DummyMethod* createDummyMethod(const char* name, Node* node, Node* paramNode) {
    DummyMethod* method = (DummyMethod*)malloc(sizeof(DummyMethod));
    if (method == NULL) {
        return NULL;
    }

    method->name = strdup(name);  // Create a copy of the name string
    if (method->name == NULL) {
        free(method);
        return NULL;
    }

    method->node = node;
    method->paramNode = paramNode;

    return method;
}

void freeDummyMethod(DummyMethod* method) {
    if (method != NULL) {
        free(method->name);
        // Note: We don't free node and paramNode here as they might be managed elsewhere
        free(method);
    }
}