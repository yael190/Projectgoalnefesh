/* file_utils.c */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_utils.h"
#include "error_handler.h"

#define MAX_FILENAME_LENGTH 256

/* פותחת קובץ .am לקריאה לפי שם בסיס */
FILE* open_am_file(const char* base_name) {
    char filename[MAX_FILENAME_LENGTH];
    build_filename(filename, base_name, ".am");
    FILE* file = fopen(filename, "r");
    if (!file) {
        report_error("שגיאה בפתיחת קובץ .am", -1);
    }
    return file;
}

/* בונה שם קובץ חדש עם סיומת נתונה */
void build_filename(char* dest, const char* base_name, const char* extension) {
    if (!dest || !base_name || !extension) return;

    size_t base_len = strlen(base_name);
    size_t ext_len = strlen(extension);

    if (base_len + ext_len >= MAX_FILENAME_LENGTH) {
        report_error("שגיאה: שם קובץ ארוך מדי", -1);
        dest[0] = '\0';
        return;
    }

    strcpy(dest, base_name);
    strcat(dest, extension);
}

/* פותחת קובץ פלט לפי סיומת */
FILE* open_output_file(const char* base_name, const char* extension) {
    char filename[MAX_FILENAME_LENGTH];
    build_filename(filename, base_name, extension);
    if (filename[0] == '\0') {
        report_error("שגיאה בבניית שם קובץ לפלט", -1);
        return NULL;
    }
    FILE* file = fopen(filename, "w");
    if (!file) {
        report_error("שגיאה ביצירת קובץ פלט", -1);
    }
    return file;
}

/* סוגרת קובץ אם הוא פתוח */
void safe_close(FILE* fp) {
    if (fp != NULL) fclose(fp);
}
