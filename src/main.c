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
