// parser_ll1.h

#ifndef PARSER_LL1_H
#define PARSER_LL1_H

#include "scanner.h"
#include "output.h"
#include "bitset_wrapper.h"
#include "symboltable.h"
#include "node.h"
#include "linkedlist.h"

typedef struct {
    Scanner *in;
    Output *out;

    Token *token;
    Token *lastToken;

    bitset64 *firstMembDecl;
    bitset64 *firstStmt;
    bitset64 *firstCondFact;

    SymbolTable *symbolTable;
    Item *classObject;
    Item *curObject;

    Node *abstractSyntaxTree;

    LinkedList *unresolvedMethods;

    bool debug;
    bool vcg;
} ParserLL1;

ParserLL1 *parser_create(Scanner *in, bool debug, bool vcg);
void parser_free(ParserLL1 *parser);

#endif
