#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
#include "token.h"
#include "output.h"

int main() {
    const char *filename = "/home/mohamad-khaled-minawe/Desktop/project/TinyJava_C/src/testFiles/testScanner.txt";

    Scanner *scanner = create_scanner(filename, 0); // Debug-Modus aktiv

    printf("Beginne Scan-Vorgang...\n");

    Token *token ;
    do {
        token = scan_symbol(scanner);
       
    } while (token->symbol != EOF_TOKEN);

 
   

    printf("\nAlle Tokens wurden gelesen.\n");

    // Fehlerbericht
    output_printErrorReport(scanner->output);
    free_scanner(scanner);   


    return 0;
}
