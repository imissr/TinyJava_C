#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "token.h"
#include "hashtable.h"
#include "input.h"
#include "output.h"

typedef struct {
    Input *input;         // Source file
    Output *output;       // Output file
    int line;            // Current line number
    int column;          // Current column number
    int isDebug;         // Debug mode
    Token *token;         // Current token
    char ch;             // Current character
    Hashtable *keywords; // Hash table for keywords
} Scanner;

// Function declarations
Scanner *create_scanner(const char *filename, int debug);
void reserve_keywords(Scanner *scanner);
Token *scan_symbol(Scanner *scanner);
char get_symbol(Scanner *scanner);
void sift_symbols(Scanner *scanner);
int check_int_range(const char *s);
char peek(Scanner *scanner);
void free_scanner(Scanner *scanner);

#endif
