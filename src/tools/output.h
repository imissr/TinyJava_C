#ifndef OUTPUT_H
#define OUTPUT_H

#include "linkedlist.h"

// Struktur für den Output-Handler
typedef struct {
    LinkedList* lexicalErrors;
    LinkedList* syntacticErrors;
    LinkedList* semanticErrors;
} Output;

// Erstellt eine neue Output-Struktur
Output* output_create();

// Fügt Fehler hinzu
void output_add_lexical_error(Output* output, int line, int col, const char* msg);
void output_add_syntactical_error(Output* output, int line, int col, const char* msg);
void output_add_semantic_error(Output* output, int line, int col, const char* msg);

// Prüft, ob Fehler vorhanden sind
int output_errorFound(Output* output);

// Fehlerberichte ausgeben
void output_printLexicalErrorReport(Output* output);
void output_printSyntacticalErrorReport(Output* output);
void output_printSemanticErrorReport(Output* output);
void  output_printErrorReport(Output* output);

// Speicher freigeben
void output_free(Output* output);

#endif // OUTPUT_H
