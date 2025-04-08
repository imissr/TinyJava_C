#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 50

// Struktur für Hash-Einträge
typedef struct HashNode {
    char *key;
    int value;
    struct HashNode *next;
} HashNode;

// Struktur für die Hash-Tabelle
typedef struct {
    HashNode **table;
} Hashtable;


Hashtable *create_hashtable();
void insert_hashtable(Hashtable *ht, const char *key, int value);
int lookup_hashtable(Hashtable *ht, const char *key);
void free_hashtable(Hashtable *ht);
unsigned int hash_function(const char *key);

#endif // HASHTABLE_H
