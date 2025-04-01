#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int symbol;
    int line;
    int column;
    char *type;
    int intValue;
    char *identifier;
}Token;


// Token-Klassen als Konstanten (mit extern)
extern const int SYM_LEFT_PARENT;
extern const int SYM_RIGHT_PARENT;
extern const int SYM_LEFT_CURVED_PARENT;
extern const int SYM_RIGHT_CURVED_PARENT;
extern const int SYM_EQUAL;
extern const int SYM_LESS;
extern const int SYM_GREATER;
extern const int SYM_LESS_EQUAL;
extern const int SYM_GREATER_EQUAL;
extern const int SYM_ASSIGN;
extern const int SYM_ADD;
extern const int SYM_SUB;
extern const int SYM_TIMES;
extern const int SYM_DIV;
extern const int SYM_DOT;
extern const int SYM_SEMICOLON;
extern const int SYM_COMMA;
extern const int SYM_IF;
extern const int SYM_ELSE;
extern const int SYM_CLASS;
extern const int SYM_FINAL;
extern const int SYM_VOID;
extern const int SYM_INT;
extern const int SYM_WHILE;
extern const int SYM_ID;
extern const int SYM_NUMBER;
extern const int SYM_LEFT_CORNERED_PARENT;
extern const int SYM_RIGHT_CORNERED_PARENT;
extern const int SYM_NEW;
extern const int SYM_RETURN;
extern const int SYM_STATIC;
extern const int SYM_UNEQUAL;
extern const int EOF_TOKEN;



Token *create_token(int symbol, int line, int column, const char *type, int intValue, const char *identifier);
void print_token( Token *token);
void free_token(Token **token);

#endif // TOKEN_H
