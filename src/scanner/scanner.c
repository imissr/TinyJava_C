#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hashtable.h"
#include "token.h"
#include "input.h"
#include "scanner.h"

/*
int main() {
    const char *test_filename = "/home/imissoldgaren/tinyjava/src/test.txt";

    printf("Creating test file...\n");
    //create_test_file(test_filename);

    printf("Initializing scanner...\n");
    Scanner *scanner = create_scanner(test_filename, 0);
    if (!scanner) {
        fprintf(stderr, "Fehler beim Erstellen des Scanners\n");
        return EXIT_FAILURE;
    }

    printf("Scanner initialized successfully!\n");
    printf("Scanning symbols from test file:\n");

    // Token-Loop
    Token *token = NULL;
    do {
        token = scan_symbol(scanner);

        if (token == NULL) {
            fprintf(stderr, "Error: scan_symbol returned NULL\n");
            break;
        }
        print_token(token);

    } while (token->symbol != EOF_TOKEN);

    output_printErrorReport(scanner->output);
    printf("Final Token: ");
    print_token(token);



    // EOF-Token freigeben
    if (token) {
        free_token(&token);
    }

    printf("Freeing scanner...\n");
    free_scanner(scanner);
    printf("Scanner freed successfully!\n");

    return 0;
}
*/

Scanner *create_scanner(const char *filename, int debug)
{

    Scanner *scanner = (Scanner *)malloc(sizeof(Scanner));
    if (!scanner)
    {
        fprintf(stderr, "Memory allocation failed for Scanner\n");
        exit(EXIT_FAILURE);
    }

    scanner->input = input_init(filename);
    if (!scanner->input)
    {
        perror("Failed to open file");
        free(scanner);
        exit(EXIT_FAILURE);
    }

    scanner->output = output_create();

    scanner->line = 1;
    scanner->column = 1;
    scanner->isDebug = debug;
    scanner->ch = input_next(scanner->input); // Read first character
    scanner->keywords = create_hashtable();   // Initialize keyword table
    scanner->token = NULL;
    reserve_keywords(scanner); // Initialize keyword table

    return scanner;
}

void reserve_keywords(Scanner *scanner)
{
    insert_hashtable(scanner->keywords, "if", SYM_IF);
    insert_hashtable(scanner->keywords, "else", SYM_ELSE);
    insert_hashtable(scanner->keywords, "class", SYM_CLASS);
    insert_hashtable(scanner->keywords, "final", SYM_FINAL);
    insert_hashtable(scanner->keywords, "void", SYM_VOID);
    insert_hashtable(scanner->keywords, "int", SYM_INT);
    insert_hashtable(scanner->keywords, "while", SYM_WHILE);
    insert_hashtable(scanner->keywords, "new", SYM_NEW);
    insert_hashtable(scanner->keywords, "return", SYM_RETURN);
    insert_hashtable(scanner->keywords, "static", SYM_STATIC);
}

Token *scan_symbol(Scanner *scanner)
{
    if (!scanner)
    {
        fprintf(stderr, "Error: scanner is NULL in scan_symbol()\n");
        exit(EXIT_FAILURE);
    }

    sift_symbols(scanner);

    if (scanner->ch == EOF || scanner->ch == -1)
    {

        printf("End of file reached!\n");
        return create_token(EOF_TOKEN, scanner->line, scanner->column, "EOF", 0, NULL);
    }

    switch (scanner->ch)
    {

    case '(':
        scanner->token = create_token(SYM_LEFT_PARENT, scanner->line, scanner->column, "SEPARATOR", 0, NULL);
        get_symbol(scanner);
        break;
    case ')':
        scanner->token = create_token(SYM_RIGHT_PARENT, scanner->line, scanner->column, "SEPARATOR", 0, NULL);
        get_symbol(scanner);
        break;
    case '{':
        scanner->token = create_token(SYM_LEFT_CURVED_PARENT, scanner->line, scanner->column, "SEPARATOR", 0, NULL);
        get_symbol(scanner);
        break;
    case '}':
        scanner->token = create_token(SYM_RIGHT_CURVED_PARENT, scanner->line, scanner->column, "SEPARATOR", 0, NULL);
        get_symbol(scanner);
        break;
    case '+':
        scanner->token = create_token(SYM_ADD, scanner->line, scanner->column, "OPERATOR", 0, NULL);
        get_symbol(scanner);
        break;
    case '-':
        scanner->token = create_token(SYM_SUB, scanner->line, scanner->column, "OPERATOR", 0, NULL);
        get_symbol(scanner);
        break;
    case '*':
        scanner->token = create_token(SYM_TIMES, scanner->line, scanner->column, "OPERATOR", 0, NULL);
        get_symbol(scanner);
        break;
    case '/':
        scanner->token = create_token(SYM_DIV, scanner->line, scanner->column, "OPERATOR", 0, NULL);
        get_symbol(scanner);
        break;
    case ';':
        scanner->token = create_token(SYM_SEMICOLON, scanner->line, scanner->column, "SEPARATOR", 0, NULL);
        get_symbol(scanner);
        break;
    case ',':
        scanner->token = create_token(SYM_COMMA, scanner->line, scanner->column, "SEPARATOR", 0, NULL);
        get_symbol(scanner);
        break;
    case '.':
        scanner->token = create_token(SYM_DOT, scanner->line, scanner->column, "SEPARATOR", 0, NULL);
        get_symbol(scanner);
        break;

    case '=':

        if (input_peek(scanner->input) == '=')
        {
            scanner->token = create_token(SYM_EQUAL, scanner->line, scanner->column, "OPERATOR", 0, NULL);
            get_symbol(scanner);
            get_symbol(scanner);
            break;
        }
        else
        {
            scanner->token = create_token(SYM_ASSIGN, scanner->line, scanner->column, "OPERATOR", 0, NULL);
        }
        get_symbol(scanner);
        break;

    case '<':
        if (input_peek(scanner->input) == '=')
        {
            scanner->token = create_token(SYM_LESS_EQUAL, scanner->line, scanner->column, "OPERATOR", 0, NULL);
            get_symbol(scanner);
            get_symbol(scanner);
            break;
        }
        else
        {
            scanner->token = create_token(SYM_LESS, scanner->line, scanner->column, "OPERATOR", 0, NULL);
        }
        get_symbol(scanner);
        break;

    case '>':
        if (input_peek(scanner->input) == '=')
        {
            scanner->token = create_token(SYM_GREATER_EQUAL, scanner->line, scanner->column, "OPERATOR", 0, NULL);
            get_symbol(scanner);
            get_symbol(scanner);

            break;
        }
        else
        {
            scanner->token = create_token(SYM_GREATER, scanner->line, scanner->column, "OPERATOR", 0, NULL);
        }

        get_symbol(scanner);
        break;

    case '!':

        if (input_peek(scanner->input) == '=')
        {
            scanner->token = create_token(SYM_UNEQUAL, scanner->line, scanner->column, "OPERATOR", 0, NULL);
            get_symbol(scanner);
            get_symbol(scanner);
            break;
        }
        else
        {
            output_add_lexical_error(scanner->output, scanner->line, scanner->column, "Expected '=' after '!'");
        }
        get_symbol(scanner);
        break;

    case EOF:
        printf("Hi im here\n");
        scanner->token = create_token(EOF_TOKEN, scanner->line, scanner->column, "EOF", 0, NULL);
        break;

    default:
        if (isalpha(scanner->ch))
        {

            char id[256] = {0};
            int i = 0;

            do
            {
                id[i++] = scanner->ch;
                get_symbol(scanner);
            } while (isalnum(scanner->ch));

            id[i] = '\0';

            int keyword_type = lookup_hashtable(scanner->keywords, id);
            if (keyword_type != -1)
            {
                scanner->token = create_token(keyword_type, scanner->line, scanner->column, "KEYWORD", 0, NULL);
            }
            else
            {
                scanner->token = create_token(SYM_ID, scanner->line, scanner->column, "IDENTIFIER", 0, id);
            }
        }
        else if (isdigit(scanner->ch))
        {
            char num[256] = {0};
            int i = 0;

            do
            {
                num[i++] = scanner->ch;
                get_symbol(scanner);
            } while (isdigit(scanner->ch));

            num[i] = '\0'; // Null terminate the string

            if (!check_int_range(num))
            {
                strcpy(num, "0");
            }
            scanner->token = create_token(SYM_NUMBER, scanner->line, scanner->column, "NUMBER", atoi(num), NULL);
        }
        else
        { // Handle unknown characters

            char msg[64];
            snprintf(msg, sizeof(msg), "unknown char '%c' found", scanner->ch);
            output_add_lexical_error(scanner->output, scanner->line, scanner->column, msg);
            get_symbol(scanner); // Skip to next character
        }
        break;
    }

    if (scanner->isDebug)
    {
        print_token(scanner->token);
    }

    return scanner->token;
}

// Read the next character from input
char get_symbol(Scanner *scanner)
{
    scanner->ch = input_next(scanner->input);
    scanner->column++;
    return scanner->ch;
}

void sift_symbols(Scanner *scanner)
{
    while (scanner->ch != EOF && scanner->ch <= ' ')
    {
        if (scanner->ch == '\n')
        {
            scanner->line++;
            scanner->column = 1;
        }
        get_symbol(scanner);
    }
}

// Check if an integer is within range
bool check_int_range(const char *s)
{
    long val = strtol(s, NULL, 10);
    if (val > 32767 || val < -32768)
    {
        printf("Lexical Error: number %s out of range (>32767)\n", s);
        return 0;
    }
    return 1;
}

void free_scanner(Scanner *scanner)
{
    if (!scanner)
        return;

    if (scanner->token)
    {
        free_token(scanner->token);
    }

    if (scanner->input)
    {
        input_close(scanner->input);
    }

    if (scanner->keywords)
    {
        free_hashtable(scanner->keywords);
    }

    if (scanner->output)
    {
        output_free(scanner->output);
    }

    free(scanner);
}
