#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Token-Klassen als Konstanten definieren
typedef enum {
    SYM_LEFT_PARENT,
    SYM_RIGHT_PARENT,
    SYM_LEFT_CURVED_PARENT,
    SYM_RIGHT_CURVED_PARENT,
    SYM_EQUAL,
    SYM_LESS,
    SYM_GREATER,
    SYM_LESS_EQUAL,
    SYM_GREATER_EQUAL,
    SYM_ASSIGN,
    SYM_ADD,
    SYM_SUB,
    SYM_TIMES,
    SYM_DIV,
    SYM_DOT,
    SYM_SEMICOLON,
    SYM_COMMA,
    SYM_IF,
    SYM_ELSE,
    SYM_CLASS,
    SYM_FINAL,
    SYM_VOID,
    SYM_INT,
    SYM_WHILE,
    SYM_ID,
    SYM_NUMBER,
    SYM_LEFT_CORNERED_PARENT,
    SYM_RIGHT_CORNERED_PARENT,
    SYM_NEW,
    SYM_RETURN,
    SYM_STATIC,
    SYM_UNEQUAL,
    EOF_TOKEN
} TokenType;

// Zeichenfolgen für Token-Symbole
extern const char *symbols[];

// Token Struktur
typedef struct {
    TokenType symbol;
    int line;
    int column;
    char *type;
    int intValue;
    char *identifier;
} Token;

// Funktionen für Token
Token *create_token(TokenType symbol, int line, int column, const char *type, int intValue, const char *identifier);
void print_token(const Token *token);
void free_token(Token *token);

#endif // TOKEN_H
