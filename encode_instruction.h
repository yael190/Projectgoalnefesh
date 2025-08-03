#ifndef ENCODE_INSTRUCTION_H
#define ENCODE_INSTRUCTION_H

#include <stdio.h>
#include "table.h"  /* כאן נמצאת ההגדרה של Symbol */

typedef struct {
    char** words;
    int count;
} WordBin;

/* פונקציות */
Symbol* find_symbol(Symbol* symbol_table, int symbol_count, const char* name);
char* encode_value_with_are(int value, int are);
WordBin* encode_instruction(const char* operand, int current_ic,
    Symbol* symbol_table, int symbol_count,
    FILE** ext_file, const char* ext_filename);
void free_wordbin(WordBin* bin);

#endif
