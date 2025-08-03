#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "encode_instruction.h"
#include "error_handler.h"

#define WORD_LENGTH 24
#define ADDRESSABLE_BITS 21

Symbol* find_symbol(Symbol* symbol_table, int symbol_count, const char* name) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            return &symbol_table[i];
        }
    }
    return NULL;
}

char* encode_value_with_are(int value, int are) {
    char* word = malloc(WORD_LENGTH + 1);
    if (!word) return NULL;
    word[WORD_LENGTH] = '\0';

    for (int i = 0; i < ADDRESSABLE_BITS; i++) {
        word[WORD_LENGTH - 1 - i] = (value >> i) & 1 ? '1' : '0';
    }

    word[0] = word[1] = word[2] = '0';
    if (are == 1) word[2] = '1'; // E
    else if (are == 2) word[1] = '1'; // R
    else if (are == 0) word[0] = '1'; // A

    return word;
}

WordBin* encode_instruction(const char* operand, int current_ic,
    Symbol* symbol_table, int symbol_count,
    FILE** ext_file, const char* ext_filename) {

    WordBin* result = malloc(sizeof(WordBin));
    if (!result) return NULL;

    result->words = malloc(sizeof(char*) * 2);
    result->count = 0;
    if (!result->words) {
        free(result);
        return NULL;
    }

    if (operand[0] == '#') {
        int value = atoi(operand + 1);
        result->words[0] = encode_value_with_are(value, 0);
        result->count = 1;
        return result;
    }

    if (strncmp(operand, "r", 1) == 0 && isdigit(operand[1])) {
        int reg_num = atoi(operand + 1);
        int value = reg_num << 2;
        result->words[0] = encode_value_with_are(value, 0);
        result->count = 1;
        return result;
    }

    int relative = 0;
    const char* label = operand;
    if (operand[0] == '&') {
        relative = 1;
        label = operand + 1;
    }

    Symbol* symbol = find_symbol(symbol_table, symbol_count, label);
    if (!symbol) {
        report_error("הסמל לא נמצא בטבלת הסמלים", -1);
        free(result->words);
        free(result);
        return NULL;
    }

    int value, are;
    if (symbol->is_external) {
        value = 0;
        are = 1;
        if (!(*ext_file)) *ext_file = fopen(ext_filename, "w");
        fprintf(*ext_file, "%s %04d\n", label, current_ic);
    }
    else if (relative) {
        value = symbol->address - current_ic;
        are = 2;
    }
    else {
        value = symbol->address;
        are = 2;
    }

    result->words[0] = encode_value_with_are(value, are);
    result->count = 1;
    return result;
}

void free_wordbin(WordBin* bin) {
    if (!bin) return;
    for (int i = 0; i < bin->count; i++) {
        free(bin->words[i]);
    }
    free(bin->words);
    free(bin);
}
