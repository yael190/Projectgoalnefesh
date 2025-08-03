#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_handler.h"
#include "macro_handler.h"
#include "string_utils.h"
#include "error_handler.h"

#define MAX_NAME_LENGTH 31
#define MAX_LINE_LENGTH 100

/*
   קוראת שמות קבצים מתוך קובץ input.txt
   ומחזירה מערך של שמות הקבצים (ללא סיומת).
   מעדכנת את fileCount בהתאם.
*/
char** read_file_list(const char* filename, int* fileCount) {
    FILE* file = fopen(filename, "r");
    char** fileNames = NULL;
    char line[MAX_NAME_LENGTH] = { 0 };
    *fileCount = 0;

    if (!file) {
        report_error("לא ניתן לפתוח את קובץ הקלט", -1);
        return NULL;
    }

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';  /* הסרת תו ירידת שורה */

        /* הקצאה מחדש למערך שמות הקבצים */
        char** temp = realloc(fileNames, (*fileCount + 1) * sizeof(char*));
        if (!temp) {
            report_error("כשל בהקצאת זיכרון לשמות קבצים", -1);
            fclose(file);
            for (int i = 0; i < *fileCount; i++) free(fileNames[i]);
            free(fileNames);
            return NULL;
        }
        fileNames = temp;

        fileNames[*fileCount] = duplicateString(line);
        if (!fileNames[*fileCount]) {
            report_error("כשל בהעתקת שם קובץ", -1);
            fclose(file);
            for (int i = 0; i < *fileCount; i++) free(fileNames[i]);
            free(fileNames);
            return NULL;
        }

        (*fileCount)++;
    }

    fclose(file);
    return fileNames;
}

/*
   מבצע קדם-עיבוד (preprocess) על כל קובץ שהוזן ברשימת הקבצים.
   עבור כל קובץ נבנה קובץ .am לאחר טיפול במקרואים.
*/
void preprocess_files(MacroTable* table, char** fileNames, int fileCount) {
    int i;
    for (i = 0; i < fileCount; i++) {
        table->errorFlag = 0;

        char inputFile[MAX_NAME_LENGTH + 4] = { 0 };
        sprintf(inputFile, "%s.as", fileNames[i]);

        printf("==> מעבד את הקובץ: %s\n", inputFile);
        process_file(table, inputFile);
    }
}

/*
   מבצע עיבוד מקרואים על קובץ קלט יחיד עם סיומת .as
   ויוצר קובץ פלט עם סיומת .am
*/
void process_file(MacroTable* table, const char* fileName) {
    FILE* inFile = fopen(fileName, "r");
    FILE* outFile = NULL;
    char outputFileName[MAX_NAME_LENGTH + 4] = { 0 };
    char line[MAX_LINE_LENGTH] = { 0 };
    int inMacroDefinition = 0;
    char macroName[MAX_NAME_LENGTH] = { 0 };

    if (!inFile) {
        char msg[100];
        snprintf(msg, sizeof(msg), "לא ניתן לפתוח את הקובץ %s לקריאה", fileName);
        report_error(msg, -1);
        return;
    }

    strcpy(outputFileName, fileName);
    {
        char* dot = strrchr(outputFileName, '.');
        if (dot && strcmp(dot, ".as") == 0) {
            *dot = '\0';
        }
    }
    strcat(outputFileName, ".am");

    outFile = fopen(outputFileName, "w");
    if (!outFile) {
        char msg[100];
        snprintf(msg, sizeof(msg), "לא ניתן ליצור את הקובץ %s", outputFileName);
        report_error(msg, -1);
        fclose(inFile);
        return;
    }

    while (fgets(line, MAX_LINE_LENGTH, inFile)) {
        char* cleanLine = trim_whitespace(line);
        char firstWord[MAX_NAME_LENGTH] = { 0 };

        if (sscanf(cleanLine, "%30s", firstWord) != 1) {
            fprintf(outFile, "%s", line);  /* שורה ריקה או תגובה */
            continue;
        }

        if (strcmp(firstWord, "mcro") == 0) {
            if (sscanf(cleanLine + 5, "%30s", macroName) != 1) {
                report_error("שגיאה בהגדרת מקרו (שם לא תקין)", -1);
                table->errorFlag = 1;
            }
            startMacroDefinition(table, macroName);
            inMacroDefinition = 1;
        }
        else if (strcmp(firstWord, "mcroend") == 0) {
            endMacroDefinition(table);
            inMacroDefinition = 0;
        }
        else if (inMacroDefinition) {
            addMacroContent(table, macroName, cleanLine);
        }
        else {
            Macro* macro = findMacro(table, firstWord);
            if (macro) {
                expandMacro(outFile, macro);
            }
            else {
                fprintf(outFile, "%s", line);
            }
        }
    }

    fclose(inFile);
    fclose(outFile);

    if (table->errorFlag) {
        report_error("נמצאו שגיאות במקרואים – הקובץ לא יעובד", -1);
        remove(outputFileName); /* מחיקת קובץ .am */
    }
    else {
        printf("==> נוצר הקובץ: %s\n", outputFileName);
    }
}
