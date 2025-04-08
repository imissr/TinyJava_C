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
#include "stdbool.h"

typedef struct
{
    Input *input;        // Source file
    Output *output;      // Output file
    int line;            // Current line number
    int column;          // Current column number
    int isDebug;         // Debug mode
    Token *token;        // Current token
    char ch;             // Current character
    Hashtable *keywords; // Hash table for keywords
} Scanner;

// Function declarations
Scanner *create_scanner(const char *filename, int debug);
//reserve keywords in the hash table
void reserve_keywords(Scanner *scanner);
// scan the next symbol and create a token
Token *scan_symbol(Scanner *scanner);
// read the next character from input
char get_symbol(Scanner *scanner);
// shift symbols to skip whitespace and comments
void shift_symbols(Scanner *scanner);
// check if an integer is within range
bool check_int_range(const char *s);
// peek the next character without consuming it
char peek(Scanner *scanner);
// free the scanner
void free_scanner(Scanner *scanner);

#endif
