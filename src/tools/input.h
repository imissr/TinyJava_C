#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>

typedef struct {
    FILE *file;
    int ch;
    int last;
} Input;

// Funktion zum Initialisieren der Eingabe
Input* input_init(const char* path);

// Liest das nächste Zeichen
char input_next(Input* input);

// Schaut das nächste Zeichen an, ohne es zu konsumieren
char input_peek(Input* input);

// Gibt das zuletzt gelesene Zeichen zurück
char input_last(Input* input);

// Schließt die Datei und gibt Speicher frei
void input_close(Input* input);

#endif
