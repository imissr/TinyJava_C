#include <stdio.h>
#include "node.h"
#include "item.h"
#include "type.h"

int main() {
    // Originale Typstruktur
    Type* intType = initType(TYPE_INT);

    // Originale Items
    Item* leftItem = createItemFull("left", KIND_VAR, NOSUBKIND, copyType(intType), 0, 0, NULL);
    Item* rightItem = createItemFull("right", KIND_VAR, NOSUBKIND, copyType(intType), 0, 0, NULL);
    Item* opItem = createItemFull("op", KIND_VAR, NOSUBKIND, copyType(intType), 0, 0, NULL);

    // Originale Nodes
    Node* leftNode = createNodeWithClass(CLASS_CONST);
    leftNode->nodeObject = leftItem;

    Node* rightNode = createNodeWithClass(CLASS_CONST);
    rightNode->nodeObject = rightItem;

   Node* opNode = createNodeFull(CLASS_BINOP, SUBCLASS_PLUS, opItem, leftNode, rightNode, NULL, NULL);

    
   Node* copiedNode = createNodeFrom(opNode);

    // Beide Bäume prüfen mit typeVisitor
   printf("Original typeVisitor: %s\n", typeVisitor(opNode) ? "true" : "false");
   printf("Copied   typeVisitor: %s\n", typeVisitor(copiedNode) ? "true" : "false");

   char buf[256];
    printf("\nOriginal:\n");
    nodeToString(opNode, buf, sizeof(buf));
    printf("%s\n", buf);

    printf("\nKopie:\n");
    nodeToString(copiedNode, buf, sizeof(buf));
    printf("%s\n", buf);


    freeNodeRecursive(opNode);  
    deleteNode(copiedNode);
    freeType(intType);      
      

    return 0;
}
