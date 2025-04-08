#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>

typedef struct {
    FILE *file;
    int ch;
    int last;
} Input;

// Function initialization
Input* input_init(const char* path);

// reads the next character from the file
char input_next(Input* input);

// see the next character without moving the file pointer
char input_peek(Input* input);

// return the last read character
char input_last(Input* input);

// free the input structure
void input_close(Input* input);

#endif
