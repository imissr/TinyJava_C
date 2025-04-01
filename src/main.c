#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
#include "token.c"

void create_test_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Fehler beim Erstellen der Testdatei");
        exit(EXIT_FAILURE);
    }

    // Testsymbole in die Datei schreiben
    fprintf(file, "( ) { } + - * / = == < <= > >= ! != ; , .");
    fclose(file);
}

int main() {
    const char *test_filename = "/home/imissoldgaren/tinyjava/src/test.txt";

    printf("Creating test file...\n");
    //create_test_file(test_filename);

    printf("Initializing scanner...\n");
    Scanner *scanner = create_scanner(test_filename, 1);
    if (!scanner) {
        fprintf(stderr, "Fehler beim Erstellen des Scanners\n");
        return EXIT_FAILURE;
    }

    printf("Scanner initialized successfully!\n");
    printf("Scanning symbols from test file:\n");

    // Token-Loop
    Token *token = NULL;
    do{
        token = scan_symbol(scanner);
       
    }while (token->symbol != EOF_TOKEN);
    
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
