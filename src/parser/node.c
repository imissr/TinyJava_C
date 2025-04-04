#include "node.h"
#include <stdlib.h>

static int globalNodeCounter = 0;


const char* kinds[] = {
    "NOCLASS", "VAR", "CONST", "BINOP", "INDEX", "WHILE",
    "IF", "IFELSE", "ASSIGN", "MEMBER", "CALL", "ENTER", 
    "CLASS", "RETURN", "NEW", "METHOD", "LENGTH"
};

const char* subkinds[] = {
    "NOSUBCLASS", "TIMES", "DIV", "ADD",
    "EQ", "LT", "GT", "LEQ", "GEQ", "SUB", "NEQ"
};

Node* createNode() {
    return createNodeFull(NOCLASS, NOSUBCLASS, NULL, NULL, NULL, NULL, NULL);
}

Node* createNodeFrom(Node* other) {
    if (!other) return NULL;
    Node* node = createNodeWithConst(
        other->nodeClass,
        other->nodeSubclass,
        other->nodeObject,
        other->left,
        other->right,
        other->parent,
        other->next,
        other->constIntValue
    );
    node->prev = other->prev;
    return node;
}

Node* createNodeWithClass(int kind) {
    return createNodeFull(kind, NOSUBCLASS, NULL, NULL, NULL, NULL, NULL);
}

Node* createNodeFull(int kind, int subkind, Item* object, Node* left, Node* right, Node* parent, Node* next) {
    return createNodeWithConst(kind, subkind, object, left, right, parent, next, 0);
}

Node* createNodeWithConst(int kind, int subkind, Item* object, Node* l, Node* r, Node* p, Node* n, int intValue) {
    Node* node = malloc(sizeof(Node));
    if (!node) return NULL;

    node->nodeClass = kind;
    node->nodeSubclass = subkind;
    node->nodeObject = object;

    node->left = l;
    node->right = r;
    node->parent = p;
    node->next = n;
    node->prev = NULL;

    node->constIntValue = intValue;
    node->no = globalNodeCounter++;

    if (l) l->parent = node;
    if (r) r->parent = node;

    return node;
}


void nodeToString(const Node* node, char* buffer, size_t bufferSize) {
    if (!node || !buffer || bufferSize == 0) {
        if (buffer && bufferSize > 0) buffer[0] = '\0';
        return;
    }

    size_t remaining = bufferSize;
    size_t offset = 0;
    int written;

    // Print class kind
    written = snprintf(buffer + offset, remaining, "%s\n", 
        node->nodeClass == NOCLASS ? "-" : kinds[node->nodeClass]);
    if (written > 0) {
        offset += written;
        remaining = (written < remaining) ? (remaining - written) : 0;
    }

    // Print subclass kind
    if (remaining > 0) {
        written = snprintf(buffer + offset, remaining, "%s\n",
            node->nodeSubclass == NOSUBCLASS ? "-" : subkinds[node->nodeSubclass]);
        if (written > 0) {
            offset += written;
            remaining = (written < remaining) ? (remaining - written) : 0;
        }
    }

    // Print name if object has a name
    if (remaining > 0) {
        written = snprintf(buffer + offset, remaining, "%s\n",
            (node->nodeObject && node->nodeObject->objectName) ? 
            node->nodeObject->objectName : "-");
        if (written > 0) {
            offset += written;
            remaining = (written < remaining) ? (remaining - written) : 0;
        }
    }

    // Print object type
    if (remaining > 0) {
        if (node->nodeObject && node->nodeObject->objectType) {
            written = snprintf(buffer + offset, remaining, "%s\n",
                node->nodeObject->objectType->types[node->nodeObject->objectType->basicType]);
        } else {
            written = snprintf(buffer + offset, remaining, "-\n");
        }
        if (written > 0) {
            offset += written;
            remaining = (written < remaining) ? (remaining - written) : 0;
        }
    }

    // Print value if object is a const object
    if (remaining > 0) {
        if (node->nodeClass == CLASS_CONST) {
            written = snprintf(buffer + offset, remaining, "%d", node->constIntValue);
        } else {
            written = snprintf(buffer + offset, remaining, "-");
        }
    }
}

void freeNode(Node* node) {
    if (!node) return;

    // First free children nodes
    if (node->left) {
        freeNode(node->left);
        node->left = NULL;
    }
    if (node->right) {
        freeNode(node->right);
        node->right = NULL;
    }
    if (node->next) {
        freeNode(node->next);
        node->next = NULL;
    }

    // Don't free nodeObject here - it should be managed separately
    // The Item structure should be freed by the caller using freeItem()
    node->nodeObject = NULL;
    
    // Clear other pointers
    node->parent = NULL;
    node->prev = NULL;

    // Finally free the node itself
    free(node);
}