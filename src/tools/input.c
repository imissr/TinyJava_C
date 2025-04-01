#include "input.h"
#include <stdlib.h> 
//tested

/*#include "input.h"
#include <stdio.h>
#include <stdlib.h>

void create_test_file(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Failed to create test file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "Hello, World!");
    fclose(file);
}

int main() {
    const char* test_file = "testfile.txt";
    create_test_file(test_file);
    
    Input* input = input_init(test_file);
    if (!input) {
        fprintf(stderr, "Failed to initialize input\n");
        return EXIT_FAILURE;
    }
    
    printf("Reading characters with input_next():\n");
    for (int i = 0; i < 5; i++) {
        printf("Read character: %c\n", input_next(input));
    }
    
    printf("Testing input_peek():\n");
    char peeked = input_peek(input);
    printf("Peeked character: %c\n", peeked);
    
    printf("Testing input_last():\n");
    char last = input_last(input);
    printf("Last character: %c\n", last);
    
    input_close(input);
    
    return EXIT_SUCCESS;
}*/

Input* input_init(const char* path) {
    Input* input = (Input*)malloc(sizeof(Input));
    if (!input) {
        perror("Memory allocation failed");
        return NULL;
    }
    input->file = fopen(path, "r");
    if (!input->file) {
        perror("Cannot open file");
        free(input);
        return NULL;
    }
    input->ch = 0;
    input->last = 0;
    return input;
}

char input_next(Input* input) {
    if (!input || !input->file) return EOF;
    input->last = input->ch;
    input->ch = fgetc(input->file);
    return (char)input->ch;
}

char input_peek(Input* input) {
    if (!input || !input->file) return EOF;
    int ch = fgetc(input->file);
    if (ch != EOF) ungetc(ch, input->file);
    return (char)ch;
}

char input_last(Input* input) {
    return (char)input->last;
}

void input_close(Input* input) {
    if (input) {
        if (input->file) fclose(input->file);
        free(input);
    }
}
