#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "item.h"
#include "type.h"
#include "symboltable.h"

extern const char *types[];

void test_node_functionality()
{
    // Step 1: Create a type (shared by both items)
    Type *type = initType(TYPE_INT);

    // Step 2: Create 2 items
    Item *item1 = createItemFull("i1", KIND_VAR, NOSUBKIND, copyType(type), 0, 0, NULL);
    Item *item2 = createItemFull("i2", KIND_VAR, NOSUBKIND, copyType(type), 0, 0, NULL);
    Item *item3 = createItemFull("i3", KIND_VAR, NOSUBKIND, copyType(type), 0, 0, NULL);
    Item *item4 = createItemFull("i4", KIND_VAR, NOSUBKIND, copyType(type), 0, 0, NULL);

    // Step 3: Build node1 → node1b
    Node *node1 = createNodeWithConst(CLASS_CONST, NOSUBCLASS, item1, NULL, NULL, NULL, NULL, 100);
    Node *node1b = createNodeWithConst(CLASS_CONST, NOSUBCLASS, item2, NULL, NULL, NULL, NULL, 101);
    attachNode(node1, node1b);

    // Delete node1 and update the chain root!
    //Node *node1Chain = deleteNodeFromChain(node1); // node1Chain now points to node1b
    deleteNode(node1); // This will delete node1 but not node1b
          

    // Step 4: Build node2 → node2b
    Node *node2 = createNodeWithConst(CLASS_CONST, NOSUBCLASS, item3, NULL, NULL, NULL, NULL, 200);
    Node *node2b = createNodeWithConst(CLASS_CONST, NOSUBCLASS, item4, NULL, NULL, NULL, NULL, 201);
    attachNode(node2, node2b);

    // Step 5: Concat the updated node1 chain (node1b) with node2 chain
    Node *fullChain = concatNodes(node1b, node2); // node1b → node2 → node2b

    // Step 5: Print all nodes in the chain
    char buf[256];
    Node *cur = fullChain;
    int i = 1;
    while (cur)
    {
        printf("Node %d:\n", i++);
        nodeToString(cur, buf, sizeof(buf));
        printf("%s\n", buf);
        cur = cur->next;
    }

    // Step 6: Clean up everything
    freeNodeRecursive(fullChain);

    freeType(type);
    printf("✅ concatNodes test completed and memory freed.\n");
}

int main()
{
    test_node_functionality();
    return 0;
}