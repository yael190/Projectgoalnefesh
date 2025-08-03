/* finalize_output.c */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "finalize_output.h"

#define BINARY_LENGTH 14
#define HEX_BUFFER_SIZE 5
#define ADDRESS_START 100

/* ממירה מחרוזת בינארית באורך 14 תווים להקסדצימלי */
char* binary_to_hex(const char* binary) {
    int i, value = 0;
    char* hex = (char*)malloc(HEX_BUFFER_SIZE);
    if (!hex) return NULL;

    if (strlen(binary) != BINARY_LENGTH) {
        fprintf(stderr, "שגיאה: אורך בינארי לא תקין לקידוד.\n");
        free(hex);
        return NULL;
    }

    for (i = 0; i < BINARY_LENGTH; i++) {
        value <<= 1;
        if (binary[i] == '1') value |= 1;
    }

    sprintf(hex, "%04X", value);
    return hex;
}

/* כותבת את קובץ .ob הכולל הוראות ונתונים בפורמט הסופי */
void write_final_ob_file(const char* base_name, char** instructions, int icf, char** data, int dcf) {
    char ob_filename[256];
    FILE* ob_file;
    int i;

    if (!instructions || !data || icf < 0 || dcf < 0) {
        fprintf(stderr, "שגיאה: נתוני קלט שגויים ביצירת קובץ הפלט.\n");
        return;
    }

    sprintf(ob_filename, "%s.ob", base_name);
    ob_file = fopen(ob_filename, "w");
    if (!ob_file) {
        fprintf(stderr, "שגיאה: לא ניתן לפתוח את קובץ הפלט .ob\n");
        return;
    }

    fprintf(ob_file, "%d %d\n", icf, dcf);

    for (i = 0; i < icf; i++) {
        if (!instructions[i]) {
            fprintf(stderr, "שגיאה: הוראה חסרה בכתובת %d\n", ADDRESS_START + i);
            continue;
        }
        char* hex = binary_to_hex(instructions[i]);
        if (hex) {
            fprintf(ob_file, "%04d %s\n", ADDRESS_START + i, hex);
            free(hex);
        }
        else {
            fprintf(stderr, "שגיאה בהמרת הוראה בכתובת %d ל-hex\n", ADDRESS_START + i);
        }
    }

    for (i = 0; i < dcf; i++) {
        if (!data[i]) {
            fprintf(stderr, "שגיאה: נתון חסר בכתובת %d\n", ADDRESS_START + icf + i);
            continue;
        }
        char* hex = binary_to_hex(data[i]);
        if (hex) {
            fprintf(ob_file, "%04d %s\n", ADDRESS_START + icf + i, hex);
            free(hex);
        }
        else {
            fprintf(stderr, "שגיאה בהמרת נתון בכתובת %d ל-hex\n", ADDRESS_START + icf + i);
        }
    }

    fclose(ob_file);
}

/* משחררת מערך של מחרוזות */
void free_string_array(char** array, int size) {
    int i;
    if (!array) return;
    for (i = 0; i < size; i++) {
        free(array[i]);
    }
    free(array);
}
