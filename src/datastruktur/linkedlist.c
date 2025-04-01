#include "linkedlist.h"

// Erstellt eine neue leere verkettete Liste
LinkedList* linkedlist_create() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (!list) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

// Fügt ein Element am Ende der Liste hinzu
void linkedlist_append(LinkedList* list, void* data) {
    LinkedListNode* newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    if (!newNode) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;

    if (!list->head) {
        list->head = newNode;
    } else {
        list->tail->next = newNode;
    }
    list->tail = newNode;
    list->size++;
}

// Entfernt das erste Element aus der Liste und gibt die gespeicherte Daten zurück
void* linkedlist_remove_first(LinkedList* list) {
    if (!list->head) return NULL;

    LinkedListNode* temp = list->head;
    void* data = temp->data;
    list->head = temp->next;

    if (!list->head) list->tail = NULL; // Falls die Liste leer ist
    free(temp);
    list->size--;
    return data;
}

// Gibt die Anzahl der Elemente in der Liste zurück
size_t linkedlist_size(LinkedList* list) {
    return list->size;
}

// Prüft, ob die Liste leer ist
int linkedlist_is_empty(LinkedList* list) {
    return list->size == 0;
}

// Gibt den Kopf der Liste zurück (ohne zu entfernen)
LinkedListNode* linkedlist_head(LinkedList* list) {
    return list->head;
}

// Gibt die gesamte Liste frei (inklusive Daten, falls gewünscht)
void linkedlist_free(LinkedList* list, void (*free_func)(void*)) {
    LinkedListNode* current = list->head;
    while (current) {
        LinkedListNode* temp = current;
        current = current->next;

        if (free_func) free_func(temp->data);
        free(temp);
    }
    free(list);
}

// Druckt die Liste (benötigt eine Druckfunktion für die Daten)
void linkedlist_print(LinkedList* list, void (*print_func)(void*)) {
    LinkedListNode* current = list->head;
    while (current) {
        print_func(current->data);
        current = current->next;
    }
    printf("\n");
}
