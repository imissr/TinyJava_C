#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

// Struktur für einen einzelnen Knoten der Liste
typedef struct LinkedListNode {
    void* data;
    struct LinkedListNode* next;
} LinkedListNode;

// Struktur für die gesamte Liste
typedef struct {
    LinkedListNode* head;
    LinkedListNode* tail;
    size_t size;
} LinkedList;

// Erstellt eine neue leere Liste
LinkedList* linkedlist_create();

// Fügt ein Element am Ende der Liste hinzu
void linkedlist_append(LinkedList* list, void* data);

// Entfernt das erste Element aus der Liste und gibt es zurück
void* linkedlist_remove_first(LinkedList* list);

// Gibt die Anzahl der Elemente in der Liste zurück
size_t linkedlist_size(LinkedList* list);

// Prüft, ob die Liste leer ist (1 = leer, 0 = nicht leer)
int linkedlist_is_empty(LinkedList* list);

// Gibt den Kopf der Liste zurück (ohne zu entfernen)
LinkedListNode* linkedlist_head(LinkedList* list);

// Gibt alle Elemente der Liste frei
void linkedlist_free(LinkedList* list, void (*free_func)(void*));

// Druckt die Liste (erfordert eine Druckfunktion für die Daten)
void linkedlist_print(LinkedList* list, void (*print_func)(void*));

#endif
