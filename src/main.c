#include <stdio.h>
#include <stdlib.h>
#include "print_abstract_syntax_tree.h"
#include "node.h"
#include "item.h"
#include "type.h"

int main() {
    // Erzeuge einen einfachen AST: class -> method -> return const 42

    // Klassenelement
    Item *classItem = createItemFull("TestClass", KIND_CLASS, NOSUBKIND,
        initTypeFull(TYPE_CLASS, NOTYPE, "TestClass"), 0, 0, NULL);
    Node *classNode = createNodeFull(CLASS_CLASS, NOSUBCLASS, classItem, NULL, NULL, NULL, NULL);

    // Methodenelement
    Item *methodItem = createItemFull("main", KIND_METHOD, NOSUBKIND,
        initType(TYPE_VOID), 1, 0, NULL);
    Node *methodNode = createNodeFull(CLASS_METHOD, NOSUBCLASS, methodItem, NULL, NULL, classNode, NULL);

    // Rückgabeknoten mit Konstante 42
    Item *constItem = createItem();
    constItem->objectType = initType(TYPE_INT);
    Node *constNode = createNodeWithConst(CLASS_CONST, NOSUBCLASS, constItem,
        NULL, NULL, methodNode, NULL, 42);

    Node *returnNode = createNodeFull(CLASS_RETURN, NOSUBCLASS, NULL,
        constNode, NULL, methodNode, NULL);
    constNode->parent = returnNode;

    // Verknüpfen
    methodNode->right = returnNode;
    classNode->left = methodNode;

    // VCG-Datei erzeugen
    print_abstract_syntax_tree(classNode, "test_ast.vcg");

    // Optional: debug-Ausgabe
    char debug[256];
    nodeToString(classNode, debug, sizeof(debug));
    printf("Root Node: %s\n", debug);

    // Aufräumen
    freeNodeRecursive(classNode);

    printf("AST wurde erfolgreich als test_ast.vcg erzeugt.\n");
    return 0;
}
