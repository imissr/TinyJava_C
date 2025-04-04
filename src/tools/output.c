#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

// Struktur für den Output-Handler
// zero memory leaks
typedef struct
{
    LinkedList *lexicalErrors;
    LinkedList *syntacticErrors;
    LinkedList *semanticErrors;
} Output;

// Erstellt eine neue Output-Struktur
Output *output_create()
{
    Output *output = (Output *)malloc(sizeof(Output));
    if (!output)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    output->lexicalErrors = linkedlist_create();
    output->syntacticErrors = linkedlist_create();
    output->semanticErrors = linkedlist_create();
    return output;
}

// Fügt einen lexikalischen Fehler hinzu
void output_add_lexical_error(Output *output, int line, int col, const char *msg)
{
    char *errorMsg = (char *)malloc(256);
    snprintf(errorMsg, 256, "- error at line %d at col %d : %s", line, col, msg);
    linkedlist_append(output->lexicalErrors, errorMsg);
}

// Fügt einen syntaktischen Fehler hinzu
void output_add_syntactical_error(Output *output, int line, int col, const char *msg)
{
    char *errorMsg = (char *)malloc(256);
    snprintf(errorMsg, 256, "- error at line %d at col %d : %s", line, col, msg);
    linkedlist_append(output->syntacticErrors, errorMsg);
}

// Fügt einen semantischen Fehler hinzu
void output_add_semantic_error(Output *output, int line, int col, const char *msg)
{
    char *errorMsg = (char *)malloc(256);
    snprintf(errorMsg, 256, "- error at line %d at col %d : %s", line, col, msg);
    linkedlist_append(output->semanticErrors, errorMsg);
}

// Prüft, ob Fehler gefunden wurden
int output_errorFound(Output *output)
{
    return !linkedlist_is_empty(output->lexicalErrors) ||
           !linkedlist_is_empty(output->syntacticErrors) ||
           !linkedlist_is_empty(output->semanticErrors);
}

// Druckt alle Fehler einer Liste
void output_printErrorList(LinkedList *list, const char *category)
{
    printf("# %s: found %zu errors\n", category, linkedlist_size(list));
    linkedlist_print(list, (void (*)(void *))puts);
}

// Druckt alle lexikalischen Fehler
void output_printLexicalErrorReport(Output *output)
{
    output_printErrorList(output->lexicalErrors, "lexical analysis");
}

// Druckt alle syntaktischen Fehler
void output_printSyntacticalErrorReport(Output *output)
{
    output_printErrorList(output->syntacticErrors, "syntactic analysis");
}

// Druckt alle semantischen Fehler
void output_printSemanticErrorReport(Output *output)
{
    output_printErrorList(output->semanticErrors, "semantic analysis");
}

void print_string_error(void *data)
{
    if (data)
    {
        printf("%s\n", (char *)data);
    }
}

void output_printErrorReport(Output *output)
{
    if (!output)
        return;

    size_t totalErrors = linkedlist_size(output->lexicalErrors) +
                         linkedlist_size(output->syntacticErrors) +
                         linkedlist_size(output->semanticErrors);

    printf("# compiler: found %zu errors\n", totalErrors);

    linkedlist_print(output->lexicalErrors, print_string_error);
    linkedlist_print(output->syntacticErrors, print_string_error);
    linkedlist_print(output->semanticErrors, print_string_error);
}

// Gibt die Output-Struktur frei
void output_free(Output *output)
{
    linkedlist_free(output->lexicalErrors, free);
    linkedlist_free(output->syntacticErrors, free);
    linkedlist_free(output->semanticErrors, free);
    free(output);
}