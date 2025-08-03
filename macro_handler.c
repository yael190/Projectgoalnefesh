#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "macro_handler.h"
#include "reserved.h"
#include "string_utils.h"

/* אתחול טבלת המקרואים */
void initMacroTable(MacroTable* table) {
    table->count = 0;
    table->macroNameCount = 0;
    table->errorFlag = 0;
}

/* התחלת הגדרת מקרו חדש (שם בלבד) */
void startMacroDefinition(MacroTable* table, const char* rawInput) {
    char name[MAX_NAME_LENGTH] = { 0 };
    int i, hasError = 0;

    /* חילוץ שם המקרו מהשורה */
    if (sscanf(rawInput, "%30s", name) != 1) {
        printf("שגיאה: שם מקרו לא חוקי\n");
        table->errorFlag = 1;
        return;
    }

    /* בדיקה אם השם הוא מילה שמורה */
    if (isReservedKeyword(name)) {
        printf("שגיאה: שם המקרו '%s' הוא מילה שמורה\n", name);
        table->errorFlag = 1;
        hasError = 1;
    }

    /* בדיקת כפילות בשם המקרו */
    for (i = 0; i < table->macroNameCount; i++) {
        if (strcmp(table->macroNames[i], name) == 0) {
            printf("שגיאה: מקרו '%s' כבר הוגדר\n", name);
            table->errorFlag = 1;
            hasError = 1;
        }
    }

    if (hasError) return;

    /* הוספת המקרו לטבלה */
    strcpy(table->macroNames[table->macroNameCount++], name);
    strcpy(table->macros[table->count].name, name);
    table->macros[table->count].lines = NULL;
    table->count++;
}

/* סיום הגדרת מקרו – פונקציה ריקה לשם השלמות */
void endMacroDefinition(MacroTable* table) {
    /* כרגע לא נדרש לבצע פעולה – ניתן להרחיב בעתיד */
}

/* חיפוש מקרו לפי שם */
Macro* findMacro(MacroTable* table, const char* name) {
    for (int i = 0; i < table->count; i++) {
        if (strcmp(table->macros[i].name, name) == 0) {
            return &table->macros[i];
        }
    }
    return NULL;
}

/* הרחבת מקרו – הדפסת שורות תוכן לקובץ פלט */
void expandMacro(FILE* outFile, Macro* macro) {
    if (!macro || !macro->lines) return;

    MacroLine* line = macro->lines;
    while (line) {
        fprintf(outFile, "    %s\n", line->line);
        line = line->next;
    }
    fprintf(outFile, "\n");
}

/* הוספת שורה לתוכן מקרו */
void addMacroContent(MacroTable* table, const char* name, const char* line) {
    Macro* macro = findMacro(table, name);
    if (!macro) return;

    MacroLine* newLine = (MacroLine*)malloc(sizeof(MacroLine));
    if (!newLine) {
        printf("שגיאה: כשל בהקצאת זיכרון לשורת מקרו\n");
        return;
    }

    char* trimmedLine = trim_whitespace(duplicateString(line));
    if (!trimmedLine) {
        printf("שגיאה: כשל בהקצאת זיכרון לשורת מקרו\n");
        free(newLine);
        return;
    }

    newLine->line = trimmedLine;
    newLine->next = NULL;

    if (!macro->lines) {
        macro->lines = newLine;
    }
    else {
        MacroLine* temp = macro->lines;
        while (temp->next) temp = temp->next;
        temp->next = newLine;
    }
}

/* שחרור כל הזיכרון שהוקצה למקרואים */
void freeMacroTable(MacroTable* table) {
    for (int i = 0; i < table->count; i++) {
        MacroLine* line = table->macros[i].lines;
        while (line) {
            MacroLine* temp = line;
            line = line->next;
            if (temp->line) free(temp->line);
            free(temp);
        }
    }
    table->count = 0;
}
