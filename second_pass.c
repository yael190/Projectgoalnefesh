#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "encode_instruction.h"
#include "file_utils.h"
#include "second_pass.h"
#include "finalize_output.h"
#include "error_handler.h"
#include "string_utils.h"
#include "file_handler.h"

/* כתובת התחלה של הוראות */
#define START_ADDRESS 100

/* מסיר קבצי פלט אם נמצאה שגיאה */
static void remove_output_files(const char* base_name) {
    char filename[MAX_LINE_LENGTH];
    build_filename(filename, base_name, ".ob"); remove(filename);
    build_filename(filename, base_name, ".ent"); remove(filename);
    build_filename(filename, base_name, ".ext"); remove(filename);
}

/*
    מבצע את המעבר השני על קובץ .am:
    - מזהה פקודות .entry ומעדכן טבלת סמלים
    - מקודד הוראות לפי טבלת סמלים
    - יוצר קבצי פלט סופיים: .ob, .ent, .ext
*/
void second_pass(const char* base_name, Symbol* symbol_table, int symbol_count, int instruction_count, int data_count) {
    char am_filename[MAX_LINE_LENGTH], ent_filename[MAX_LINE_LENGTH], ext_filename[MAX_LINE_LENGTH];
    FILE* am_file, * ent_file = NULL, * ext_file = NULL;
    char line[MAX_LINE_LENGTH];
    int ic = START_ADDRESS, dc = 0, line_number = 0;

    reset_errors();
    build_filename(am_filename, base_name, ".am");
    build_filename(ent_filename, base_name, ".ent");
    build_filename(ext_filename, base_name, ".ext");

    am_file = open_am_file(base_name);
    if (!am_file) {
        report_error("לא ניתן לפתוח את קובץ .am", -1);
        return;
    }

    if (instruction_count < 0 || data_count < 0) {
        report_error("כמות הוראות או נתונים לא תקינה במעבר השני", -1);
        fclose(am_file);
        return;
    }

    char** instructions = malloc(sizeof(char*) * instruction_count);
    char** data = malloc(sizeof(char*) * data_count);
    if (!instructions || !data) {
        report_error("כשל בהקצאת זיכרון למערכי הפלט", -1);
        fclose(am_file);
        if (instructions) free(instructions);
        if (data) free(data);
        return;
    }

    int inst_index = 0, data_index = 0;

    while (fgets(line, sizeof(line), am_file)) {
        line_number++;
        char* token = strtok(line, " \t\n");
        if (!token || token[0] == ';') continue;
        if (token[strlen(token) - 1] == ':') token = strtok(NULL, " \t\n");
        if (!token) continue;

        if (strcmp(token, ".entry") == 0) {
            char* label_name = strtok(NULL, " \t\n");
            if (!label_name) {
                report_error(".entry ללא שם תווית", line_number);
                continue;
            }
            Symbol* symbol = find_symbol(symbol_table, symbol_count, label_name);
            if (!symbol) {
                report_error("סמל ב-.entry לא קיים בטבלת הסמלים", line_number);
            }
            else {
                symbol->is_entry = 1;
                if (!ent_file) ent_file = fopen(ent_filename, "w");
                fprintf(ent_file, "%s %04d\n", label_name, symbol->address);
            }
        }
        else if (strcmp(token, ".data") == 0) {
            char* num_str;
            while ((num_str = strtok(NULL, ", \t\n")) != NULL) {
                int value = atoi(num_str);
                data[data_index++] = encode_value_with_are(value, 0);
                dc++;
            }
        }
        else if (strcmp(token, ".string") == 0) {
            char* str = strchr(line, '"');
            if (!str) continue;
            str++;
            char* end = strchr(str, '"');
            if (end) *end = '\0';
            for (int i = 0; i < strlen(str); i++) {
                data[data_index++] = encode_value_with_are((int)str[i], 0);
                dc++;
            }
            data[data_index++] = encode_value_with_are(0, 0);
            dc++;
        }
        else {
            char* operands[2] = { NULL, NULL };
            char* raw_operands = strchr(line, ' ');
            if (raw_operands) {
                raw_operands++;
                operands[0] = strtok(raw_operands, ",");
                operands[1] = strtok(NULL, ",");
            }

            int bin_words = 0;
            for (int i = 0; i < 2; i++) {
                if (operands[i]) {
                    trim_whitespace(operands[i]);
                    WordBin* bin = encode_instruction(operands[i], ic + bin_words, symbol_table, symbol_count, &ext_file, ext_filename);
                    if (!bin) {
                        report_error(i == 0 ? "כשל בקידוד אופנד ראשון" : "כשל בקידוד אופנד שני", line_number);
                    }
                    else {
                        for (int j = 0; j < bin->count; j++) {
                            instructions[inst_index++] = duplicateString(bin->words[j]);  // ✅ במקום strdup
                        }
                        bin_words += bin->count;
                        free_wordbin(bin);
                    }
                }
            }
            ic += bin_words;
        }
    }

    fclose(am_file);
    if (ent_file) fclose(ent_file);
    if (ext_file) fclose(ext_file);

    if (has_errors()) {
        printf("\n המעבר השני נכשל עבור הקובץ %s. הפלט לא נשמר.\n", base_name);
        print_errors();
        remove_output_files(base_name);
    }
    else {
        write_final_ob_file(base_name, instructions, inst_index, data, data_index);
    }

    free_string_array(instructions, inst_index);
    free_string_array(data, data_index);
}
