#include "hashtable.h"
// zero memory leaks
// Erstelle eine neue Hash-Tabelle
Hashtable *create_hashtable() {
    Hashtable *ht = (Hashtable *)malloc(sizeof(Hashtable));
    if (!ht) {
        fprintf(stderr, "Memory allocation failed for Hashtable\n");
        exit(EXIT_FAILURE);
    }

    ht->table = (HashNode **)malloc(TABLE_SIZE * sizeof(HashNode *));
    if (!ht->table) {
        fprintf(stderr, "Memory allocation failed for Hashtable table\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }

    return ht;
}

// Eintrag in die Hash-Tabelle einfügen
void insert_hashtable(Hashtable *ht, const char *key, int value) {
    unsigned int index = hash_function(key);
    HashNode *new_node = (HashNode *)malloc(sizeof(HashNode));

    if (!new_node) {
        fprintf(stderr, "Memory allocation failed for HashNode\n");
        exit(EXIT_FAILURE);
    }

    new_node->key = strdup(key);
    new_node->value = value;
    new_node->next = ht->table[index];
    ht->table[index] = new_node;
}

// Eintrag aus der Hash-Tabelle suchen
int lookup_hashtable(Hashtable *ht, const char *key) {
    unsigned int index = hash_function(key);
    HashNode *node = ht->table[index];

    while (node) {
        if (strcmp(node->key, key) == 0) {
            return node->value;
        }
        node = node->next;
    }

    return -1; // Nicht gefunden
}

// Speicher der Hash-Tabelle freigeben
void free_hashtable(Hashtable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode *node = ht->table[i];
        while (node) {
            HashNode *temp = node;
            node = node->next;
            free(temp->key);
            free(temp);
        }
    }
    free(ht->table);
    free(ht);
}

// Einfache Hash-Funktion
unsigned int hash_function(const char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + *key++;
    }
    return hash % TABLE_SIZE;
}
