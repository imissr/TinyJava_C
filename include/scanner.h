#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "token.h"
#include "input.h"
#include "output.h"

#define HASH_SIZE 50

// Struktur für den Scanner
typedef struct {
    Input *in;
    Output *out;
    int line;
    int column;
    int isDebug;
    char ch;
    Token *token;
    Hashtable *keywords;
} Scanner;

// Funktion zur Erstellung eines Scanners
Scanner *create_scanner(Input *in, Output *out, int debug);
void reserve_keywords(Scanner *scanner);
Token *scan_symbol(Scanner *scanner);
void sift_symbols(Scanner *scanner);
char get_symbol(Scanner *scanner);
int check_int_range(Scanner *scanner, const char *num);
void free_scanner(Scanner *scanner);

#endif // SCANNER_H
