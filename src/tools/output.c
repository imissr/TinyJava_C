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


void output_add_lexical_error(Output *output, int line, int col, const char *msg)
{
    char *errorMsg = (char *)malloc(256);
    snprintf(errorMsg, 256, "- error at line %d at col %d : %s", line, col, msg);
    linkedlist_append(output->lexicalErrors, errorMsg);
}


void output_add_syntactical_error(Output *output, int line, int col, const char *msg)
{
    char *errorMsg = (char *)malloc(256);
    snprintf(errorMsg, 256, "- error at line %d at col %d : %s", line, col, msg);
    linkedlist_append(output->syntacticErrors, errorMsg);
}


void output_add_semantic_error(Output *output, int line, int col, const char *msg)
{
    char *errorMsg = (char *)malloc(256);
    snprintf(errorMsg, 256, "- error at line %d at col %d : %s", line, col, msg);
    linkedlist_append(output->semanticErrors, errorMsg);
}


int output_errorFound(Output *output)
{
    return !linkedlist_is_empty(output->lexicalErrors) ||
           !linkedlist_is_empty(output->syntacticErrors) ||
           !linkedlist_is_empty(output->semanticErrors);
}


void output_printErrorList(LinkedList *list, const char *category)
{
    printf("# %s: found %zu errors\n", category, linkedlist_size(list));
    linkedlist_print(list, (void (*)(void *))puts);
}

void output_printLexicalErrorReport(Output *output)
{
    output_printErrorList(output->lexicalErrors, "lexical analysis");
}


void output_printSyntacticalErrorReport(Output *output)
{
    output_printErrorList(output->syntacticErrors, "syntactic analysis");
}


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

void output_free(Output *output)
{
    linkedlist_free(output->lexicalErrors, free);
    linkedlist_free(output->syntacticErrors, free);
    linkedlist_free(output->semanticErrors, free);
    free(output);
}