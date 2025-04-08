#ifndef PRINT_AST_H
#define PRINT_AST_H

#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Exportiert den gegebenen AST als VCG-Datei
void print_abstract_syntax_tree(Node *root, const char *filename);

#endif
