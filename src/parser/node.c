#include "node.h"

/*
tested the tostring method
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "item.h"
#include "type.h"



int main() {
    // Initialisiere einen Typ
    Type* t = initType(TYPE_INT);

    // Erzeuge ein Item
    Item* item = createItemFull("myConst", KIND_VAR, NOSUBKIND, t, 0, 0, NULL);

    // Erzeuge einen Node
    Node* node = createNodeWithConst(CLASS_CONST, NOSUBCLASS, item, NULL, NULL, NULL, NULL, 42);

    // String-Puffer für Ausgabe
    char buffer[256];
    nodeToString(node, buffer, sizeof(buffer));

    // Ausgabe
    printf("Node:\n%s\n", buffer);

    // Speicher freigeben
    if (item) {
        freeItem(item);  // Free item first
        item = NULL;
    }

    if (node) {
        freeNode(node);  // Then free node
        node = NULL;
    }
    return 0;
}
*/

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "item.h"
#include "type.h"
#include "symboltable.h"

extern const char* types[];

void test_node_functionality() {
    // Create types
    Type* intType = initType(TYPE_INT);
    Type* boolType = initType(TYPE_BOOLEAN);
    Type* voidType = initType(TYPE_VOID);
    Type* classTypeA = initTypeFull(TYPE_CLASS, NOTYPE, "MyClass");
    Type* classTypeB = initTypeFull(TYPE_CLASS, NOTYPE, "OtherClass");

    // Create items
    Item* varItem = createItemFull("x", KIND_VAR, NOSUBKIND, intType, 0, 0, NULL);
    Item* constItem = createItemFull("c", KIND_VAR, NOSUBKIND, intType, 0, 0, NULL);
    Item* boolItem = createItemFull("b", KIND_VAR, NOSUBKIND, boolType, 0, 0, NULL);
    Item* classItemA = createItemFull("objA", KIND_VAR, NOSUBKIND, classTypeA, 0, 0, NULL);
    Item* classItemB = createItemFull("objB", KIND_VAR, NOSUBKIND, classTypeB, 0, 0, NULL);
    //Item* staticItem = createItemFull("staticVar", KIND_VAR, NOSUBKIND, intType, 1, 0, NULL);
    Item* methodItem = createItemFull("myMethod", KIND_METHOD, NOSUBKIND, voidType, 1, 0, NULL);

    // Set up parent relationship for staticMethodVisitor
    //SymbolTable* methodTable = createSymbolTable(NULL);
    //methodTable->parent = methodItem;
    //staticItem->parentTable = methodTable;

    // Create basic nodes
    Node* constNode = createNodeWithConst(CLASS_CONST, NOSUBCLASS, constItem, NULL, NULL, NULL, NULL, 42);
    Node* varNode = createNodeFull(CLASS_VAR, NOSUBCLASS, varItem, NULL, NULL, NULL, NULL);
    Node* binopNode = createNodeFull(CLASS_BINOP, SUBCLASS_PLUS, constItem, constNode, varNode, NULL, NULL);

    // Test copy constructor
    Node* copyNode = createNodeFrom(binopNode);

    // Test attachNode
    attachNode(binopNode, copyNode);

    // Test concatNodes
    Node* anotherNode = createNodeWithConst(CLASS_CONST, NOSUBCLASS, constItem, NULL, NULL, NULL, NULL, 7);
    Node* concat = concatNodes(copyNode, anotherNode);

    // Test deleteNode (deletes copyNode)
    deleteNode(copyNode);

    // Test typeVisitor
    Node* boolLeft = createNodeFull(CLASS_VAR, NOSUBCLASS, boolItem, NULL, NULL, NULL, NULL);
    Node* boolRight = createNodeFull(CLASS_VAR, NOSUBCLASS, boolItem, NULL, NULL, NULL, NULL);
    Node* booleanCompare = createNodeFull(CLASS_BINOP, SUBCLASS_EQ, boolItem, boolLeft, boolRight, NULL, NULL);

    printf("typeVisitor (bool == bool): %s\n", typeVisitor(booleanCompare) ? "true" : "false");

    // Test staticMethodVisitor
    //Node* staticUse = createNodeFull(CLASS_VAR, NOSUBCLASS, staticItem, NULL, NULL, NULL, NULL);
    //Node* methodRoot = createNodeFull(CLASS_METHOD, NOSUBCLASS, methodItem, staticUse, NULL, NULL, NULL);
    //printf("staticMethodVisitor (allowed): %s\n", staticMethodVisitor(methodRoot) ? "true" : "false");

    // Test returnMethodVisitor
    Node* ret1 = createNodeFull(CLASS_RETURN, NOSUBCLASS, NULL, NULL, NULL, NULL, NULL);
    Node* ret2 = createNodeFull(CLASS_VAR, NOSUBCLASS, varItem, NULL, NULL, NULL, NULL);
    ret1->next = ret2;
    printf("returnMethodVisitor (should be false): %s\n", returnMethodVisitor(ret1) ? "true" : "false");

    Node* finalReturn = createNodeFull(CLASS_RETURN, NOSUBCLASS, NULL, NULL, NULL, NULL, NULL);
    printf("returnMethodVisitor (should be true): %s\n", returnMethodVisitor(finalReturn) ? "true" : "false");

    // Test toString
    char buffer[256];
    printf("\nNode.toString() test:\n");
    nodeToString(constNode, buffer, sizeof(buffer));
    printf("%s\n", buffer);
    nodeToString(binopNode, buffer, sizeof(buffer));
    printf("%s\n", buffer);
    nodeToString(booleanCompare, buffer, sizeof(buffer));
    printf("%s\n", buffer);

    // Cleanup
    freeNode(constNode);
    freeNode(varNode);
    freeNode(binopNode);
    freeNode(anotherNode);
    freeNode(boolLeft);
    freeNode(boolRight);
    freeNode(booleanCompare);
    //freeNode(staticUse);
    //freeNode(methodRoot);
    freeNode(ret1);
    freeNode(ret2);
    freeNode(finalReturn);

    freeItem(varItem);
    freeItem(constItem);
    freeItem(boolItem);
    freeItem(classItemA);
    freeItem(classItemB);
    //freeItem(staticItem);
    freeItem(methodItem);

    freeType(intType);
    freeType(boolType);
    freeType(voidType);
    freeType(classTypeA);
    freeType(classTypeB);

}

int main() {
    test_node_functionality();
    return 0;
}*/

static int globalNodeCounter = 0;

const char *kinds[] = {
    "NOCLASS", "VAR", "CONST", "BINOP", "INDEX", "WHILE",
    "IF", "IFELSE", "ASSIGN", "MEMBER", "CALL", "ENTER",
    "CLASS", "RETURN", "NEW", "METHOD", "LENGTH"};

const char *subkinds[] = {
    "NOSUBCLASS", "TIMES", "DIV", "ADD",
    "EQ", "LT", "GT", "LEQ", "GEQ", "SUB", "NEQ"};

Node *createNode()
{
    return createNodeFull(NOCLASS, NOSUBCLASS, NULL, NULL, NULL, NULL, NULL);
}

Node *createNodeFrom(Node *other)
{
    if (!other)
        return NULL;
    Node *node = createNodeWithConst(
        other->nodeClass,
        other->nodeSubclass,
        other->nodeObject,
        other->left,
        other->right,
        other->parent,
        other->next,
        other->constIntValue);
    node->prev = other->prev;
    return node;
}

Node *createNodeWithClass(int kind)
{
    return createNodeFull(kind, NOSUBCLASS, NULL, NULL, NULL, NULL, NULL);
}

Node *createNodeFull(int kind, int subkind, Item *object, Node *left, Node *right, Node *parent, Node *next)
{
    return createNodeWithConst(kind, subkind, object, left, right, parent, next, 0);
}

Node *createNodeWithConst(int kind, int subkind, Item *object, Node *l, Node *r, Node *p, Node *n, int intValue)
{
    Node *node = malloc(sizeof(Node));
    if (!node)
        return NULL;

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

    if (l)
        l->parent = node;
    if (r)
        r->parent = node;

    return node;
}

void attachNode(Node *base, Node *node)
{
    if (!base || !node)
        return;

    if (base->next == NULL)
    {
        base->next = node;
        node->prev = base;
    }
    else
    {
        Node *temp = base->next;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = node;
        node->prev = temp;
    }
}

Node *concatNodes(Node *first, Node *second)
{
    if (!first)
        return second;
    if (!second)
        return first;

    Node *temp = first;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = second;
    return first;
}

void deleteNode(Node *node)
{
    if (!node)
        return;

    if (node->prev == NULL || node->prev->nodeClass == NOCLASS)
    {
        if (node->next == NULL)
        {
            if (node->parent)
            {
                node->parent->right = NULL;
            }
        }
        else
        {
            if (node->parent)
            {
                node->parent->right = node->next;
                node->next->parent = node->parent;
            }
        }
    }
    else
    {
        if (node->next == NULL)
        {
            node->prev->next = NULL;
        }
        else
        {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
    }
}

bool typeVisitor(const Node *node)
{
    if (!node || !node->nodeObject || !node->nodeObject->objectType)
    {
        return false;
    }

    // Check member, index, or array length selections
    if (node->nodeClass == CLASS_SELECT_MEMBER ||
        node->nodeClass == CLASS_SELECT_INDEX ||
        node->nodeClass == CLASS_ARRAYLENGTH)
    {
        return true;
    }

    // Check void, array, or class types
    if (node->nodeObject->objectType->basicType == TYPE_VOID ||
        node->nodeObject->objectType->basicType == TYPE_ARRAY ||
        node->nodeObject->objectType->basicType == TYPE_CLASS)
    {
        return !(node->right || node->left);
    }

    // Check integer type
    if (node->nodeObject->objectType->basicType == TYPE_INT)
    {
        // Check left child type
        if (node->left && (!node->left->nodeObject ||
                           node->left->nodeObject->objectType->basicType != TYPE_INT))
        {
            return false;
        }
        // Check right child type
        if (node->right && (!node->right->nodeObject ||
                            node->right->nodeObject->objectType->basicType != TYPE_INT))
        {
            return false;
        }
        // No children
        if (!node->right && !node->left)
        {
            return true;
        }
        // Both children
        if (node->left && node->right)
        {
            return typeVisitor(node->left) && typeVisitor(node->right);
        }
        // Single child
        if (node->left)
            return typeVisitor(node->left);
        if (node->right)
            return typeVisitor(node->right);
    }

    // Check boolean type
    if (node->nodeObject->objectType->basicType == TYPE_BOOLEAN)
    {
        // Equality or inequality operators
        if (node->nodeSubclass == SUBCLASS_EQ || node->nodeSubclass == SUBCLASS_UNEQUAL)
        {
            if (!node->right && !node->left)
                return true;

            if (!node->left || !node->right || !node->left->nodeObject ||
                !node->right->nodeObject || !node->left->nodeObject->objectType ||
                !node->right->nodeObject->objectType)
            {
                return false;
            }

            // Check if types match
            if (node->left->nodeObject->objectType->basicType !=
                node->right->nodeObject->objectType->basicType)
            {
                return false;
            }

            // Check class types specifically
            if (node->left->nodeObject->objectType->basicType == TYPE_CLASS &&
                node->right->nodeObject->objectType->basicType == TYPE_CLASS)
            {
                if (strcmp(node->left->nodeObject->objectType->classType,
                           node->right->nodeObject->objectType->classType) != 0)
                {
                    return false;
                }
            }

            return typeVisitor(node->left) && typeVisitor(node->right);
        }
        // Comparison operators (<, <=, >=, >)
        else
        {
            if (node->left && (!node->left->nodeObject ||
                               (node->left->nodeObject->objectType->basicType != TYPE_INT &&
                                node->left->nodeObject->objectType->basicType != TYPE_BOOLEAN)))
            {
                return false;
            }
            if (node->right && (!node->right->nodeObject ||
                                (node->right->nodeObject->objectType->basicType != TYPE_INT &&
                                 node->right->nodeObject->objectType->basicType != TYPE_BOOLEAN)))
            {
                return false;
            }
            if (!node->right && !node->left)
                return true;
            return typeVisitor(node->left) && typeVisitor(node->right);
        }
    }

    return false;
}

bool staticMethodVisitor(const Node *node)
{
    // if(!node) return 1;

    if (node->nodeClass == CLASS_SELECT_MEMBER)
    {
        return staticMethodVisitor(node->left);
    }

    if (node->nodeClass == CLASS_METHOD || (node->nodeClass == CLASS_VAR && getParent(node->nodeObject)->itemKind != KIND_METHOD))
    {

        if (node->nodeObject && !node->nodeObject->staticModifier)
        {
            return false;
        }
    }

    // Check children nodes
    if (node->left && node->right)
    {
        return staticMethodVisitor(node->left) && staticMethodVisitor(node->right);
    }
    if (node->right)
    {
        return staticMethodVisitor(node->right);
    }
    if (node->left)
    {
        return staticMethodVisitor(node->left);
    }

    return true;
}

bool returnMethodVisitor(const Node *node)
{
    if (!node)
        return false;

    if (node->next)
    {
        return returnMethodVisitor(node->next);
    }
    else if (node->nodeClass != CLASS_RETURN)
    {
        return false;
    }
    return true;
}

void nodeToString(const Node *node, char *buffer, size_t bufferSize)
{
    if (!node || !buffer || bufferSize == 0)
    {
        if (buffer && bufferSize > 0)
            buffer[0] = '\0';
        return;
    }

    size_t remaining = bufferSize;
    size_t offset = 0;
    int written;

    // Print class kind
    written = snprintf(buffer + offset, remaining, "%s\n",
                       node->nodeClass == NOCLASS ? "-" : kinds[node->nodeClass]);
    if (written > 0)
    {
        offset += written;
        remaining = (written < remaining) ? (remaining - written) : 0;
    }

    // Print subclass kind
    if (remaining > 0)
    {
        written = snprintf(buffer + offset, remaining, "%s\n",
                           node->nodeSubclass == NOSUBCLASS ? "-" : subkinds[node->nodeSubclass]);
        if (written > 0)
        {
            offset += written;
            remaining = (written < remaining) ? (remaining - written) : 0;
        }
    }

    // Print name if object has a name
    if (remaining > 0)
    {
        written = snprintf(buffer + offset, remaining, "%s\n",
                           (node->nodeObject && node->nodeObject->objectName) ? node->nodeObject->objectName : "-");
        if (written > 0)
        {
            offset += written;
            remaining = (written < remaining) ? (remaining - written) : 0;
        }
    }

    // Print object type
    if (remaining > 0)
    {
        if (node->nodeObject && node->nodeObject->objectType)
        {
            written = snprintf(buffer + offset, remaining, "%s\n",
                               node->nodeObject->objectType->types[node->nodeObject->objectType->basicType]);
        }
        else
        {
            written = snprintf(buffer + offset, remaining, "-\n");
        }
        if (written > 0)
        {
            offset += written;
            remaining = (written < remaining) ? (remaining - written) : 0;
        }
    }

    // Print value if object is a const object
    if (remaining > 0)
    {
        if (node->nodeClass == CLASS_CONST)
        {
            written = snprintf(buffer + offset, remaining, "%d", node->constIntValue);
        }
        else
        {
            written = snprintf(buffer + offset, remaining, "-");
        }
    }
}

void freeNode(Node* node) {
    if (!node) return;
    
    // Break circular references
    if (node->next) {
        node->next->prev = NULL;
        node->next = NULL;
    }
    if (node->prev) {
        node->prev->next = NULL;
        node->prev = NULL;
    }
    
    // Clear parent/child relationships
    if (node->left) {
        node->left->parent = NULL;
        node->left = NULL;
    }
    if (node->right) {
        node->right->parent = NULL;
        node->right = NULL;
    }
    if (node->parent) {
        node->parent = NULL;
    }
    
    // Don't free nodeObject here - it's managed separately
    node->nodeObject = NULL;
    
    free(node);
}