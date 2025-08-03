#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macro_handler.h"
#include "file_utils.h"
#include "firstPass.h"
#include "second_pass.h"
#include "table.h"
#include "file_handler.h"
#include "error_handler.h"

int main(void) {
    char** fileNames = NULL;
    int fileCount = 0;
    int i;

    MacroTable macroTable;
    initMacroTable(&macroTable);

    fileNames = read_file_list("input.txt", &fileCount);
    if (!fileNames) {
        fprintf(stderr, "שגיאה בקריאת קבצים מ-input.txt\n");
        return 1;
    }

    preprocess_files(&macroTable, fileNames, fileCount);

    for (i = 0; i < fileCount; i++) {
        Label* labels = NULL;
        int labelCount = 0;
        int instruction_count = 0;
        int data_count = 0;

        printf("\nמתחיל מעבר ראשון לקובץ %s\n", fileNames[i]);

        if (!first_pass_file(fileNames[i], &labels, &labelCount, &instruction_count, &data_count)) {
            printf("שגיאות במעבר הראשון – דילוג על הקובץ %s\n", fileNames[i]);
            free(labels);
            continue;
        }

        printf("מעבר ראשון הסתיים בהצלחה לקובץ %s\n", fileNames[i]);

        printf("\nמתחיל מעבר שני לקובץ %s\n", fileNames[i]);
        Symbol* symbols = convert_labels_to_symbols(labels, labelCount);
        if (!symbols) {
            free(labels);
            continue;
        }

        second_pass(fileNames[i], symbols, labelCount, instruction_count, data_count);

        free(symbols);
        free(labels);
    }

    for (i = 0; i < fileCount; i++) {
        free(fileNames[i]);
    }
    free(fileNames);

    return 0;
}
