
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
//#include "../include/token.h"

// Token-Klassen als Konstanten definieren

const int SYM_LEFT_PARENT = 0;
const int SYM_RIGHT_PARENT = 1;
const int SYM_LEFT_CURVED_PARENT = 2;
const int SYM_RIGHT_CURVED_PARENT = 3;
const int SYM_EQUAL = 4;
const int SYM_LESS = 5;
const int SYM_GREATER = 6;
const int SYM_LESS_EQUAL = 7;
const int SYM_GREATER_EQUAL = 8;
const int SYM_ASSIGN = 9;
const int SYM_ADD = 10;
const int SYM_SUB = 11;
const int SYM_TIMES = 12;
const int SYM_DIV = 13;
const int SYM_DOT = 14;
const int SYM_SEMICOLON = 15;
const int SYM_COMMA = 16;
const int SYM_IF = 17;
const int SYM_ELSE = 18;
const int SYM_CLASS = 19;
const int SYM_FINAL = 20;
const int SYM_VOID = 21;
const int SYM_INT = 22;
const int SYM_WHILE = 23;
const int SYM_ID = 24;
const int SYM_NUMBER = 25;
const int SYM_LEFT_CORNERED_PARENT = 26;
const int SYM_RIGHT_CORNERED_PARENT = 27;
const int SYM_NEW = 28;
const int SYM_RETURN = 29;
const int SYM_STATIC = 30;
const int SYM_UNEQUAL = 31;
const int EOF_TOKEN = 32;



// Zeichenfolgen für Token-Symbole
static const char *symbols[] = {
    "(", ")", "{", "}", "==", "<", ">", "<=",
    ">=", "=", "+", "-", "*", "/", ".", ";", ",", "if", "else", "class", "final",
    "void", "int", "while", "IDENTIFIER", "NUMBER", "[", "]", "new", "return",
    "static", "!=", "EOF"
};

Token *create_token(int symbol, int line, int column, const char *type, int intValue, const char *identifier) {
    Token *token = (Token *)malloc(sizeof(Token));
    if (!token) {
        fprintf(stderr, "Memory allocation failed for Token\n");
        exit(EXIT_FAILURE);
    }

    token->symbol = symbol;
    token->line = line;
    token->column = column;

    // Prüfen, ob `type` ein statischer String ist (z. B. aus einer Symboltabelle)
    token->type = type ? strdup(type) : NULL;

    token->intValue = intValue;
    
    // Falls `identifier` bereits dynamisch ist, verwende direkt `malloc()`
    token->identifier = identifier ? strdup(identifier) : NULL;

    return token;
}

// Funktion zur Darstellung des Tokens als String
void print_token( Token *token) {
    if (!token) return;
    if(token == NULL) {
        printf("Token is NULL\n");
        return;
    }
    printf("line %d, col %d: %s ", token->line, token->column, token->type);
    if (token->symbol == SYM_NUMBER) {
        printf("%d", token->intValue);
    } else if (token->symbol == SYM_ID && token->identifier) {
        printf("%s", token->identifier);
    } else if (token->symbol == EOF_TOKEN) {
        printf("EOF");
    } else {
        printf("%s", symbols[token->symbol]);
    }
    printf("\n");
}

void free_token(Token **token) {
    if (!token || !(*token)) {
        return; // Falls der Zeiger bereits NULL ist, nichts tun
    }

    printf("Freeing token: %p (type=%s, identifier=%s)\n",
           (void *)(*token),
           (*token)->type ? (*token)->type : "NULL",
           (*token)->identifier ? (*token)->identifier : "NULL");

    // Speicher für type freigeben, falls vorhanden
    if ((*token)->type) {
        free((*token)->type);
        (*token)->type = NULL;
    }
    
    // Speicher für identifier freigeben, falls vorhanden
    if ((*token)->identifier) {
        free((*token)->identifier);
        (*token)->identifier = NULL;
    }

    // Speicher für das Token selbst freigeben
    free(*token);
    *token = NULL; // Setze den Zeiger auf NULL, um doppelte Freigaben zu verhindern
}

