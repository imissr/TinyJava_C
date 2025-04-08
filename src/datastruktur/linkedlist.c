#include "linkedlist.h"
//zero memory leaks

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


void* linkedlist_remove_first(LinkedList* list) {
    if (!list->head) return NULL;

    LinkedListNode* temp = list->head;
    void* data = temp->data;
    list->head = temp->next;

    if (!list->head) list->tail = NULL; 
    free(temp);
    list->size--;
    return data;
}


size_t linkedlist_size(LinkedList* list) {
    return list->size;
}


bool linkedlist_is_empty(LinkedList* list) {
    return list->size == 0;
}


LinkedListNode* linkedlist_head(LinkedList* list) {
    return list->head;
}


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


void linkedlist_print(LinkedList* list, void (*print_func)(void*)) {
    LinkedListNode* current = list->head;
    while (current) {
        print_func(current->data);
        current = current->next;
    }
    printf("\n");
}


