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

void freeNode(Node *node)
{
    if (!node)
        return;

    // First free children nodes
    if (node->left)
    {
        freeNode(node->left);
        node->left = NULL;
    }
    if (node->right)
    {
        freeNode(node->right);
        node->right = NULL;
    }
    if (node->next)
    {
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