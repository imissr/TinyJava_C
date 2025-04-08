#ifndef OUTPUT_H
#define OUTPUT_H

#include "linkedlist.h"

// structure for the output handler
typedef struct {
    LinkedList* lexicalErrors;
    LinkedList* syntacticErrors;
    LinkedList* semanticErrors;
} Output;

// initializes the output handler
Output* output_create();

// adds errors to the output handler
void output_add_lexical_error(Output* output, int line, int col, const char* msg);
void output_add_syntactical_error(Output* output, int line, int col, const char* msg);
void output_add_semantic_error(Output* output, int line, int col, const char* msg);

// check if any errors were found
int output_errorFound(Output* output);

// prints the error report
void output_printLexicalErrorReport(Output* output);
void output_printSyntacticalErrorReport(Output* output);
void output_printSemanticErrorReport(Output* output);
void  output_printErrorReport(Output* output);

// free the output handler
void output_free(Output* output);

#endif // OUTPUT_H
