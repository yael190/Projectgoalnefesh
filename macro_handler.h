#ifndef MACRO_HANDLER_H
#define MACRO_HANDLER_H

#include <stdio.h>

#define MAX_MACROS 100
#define MAX_NAME_LENGTH 31
#define MAX_LINE_LENGTH 100

/* טיפוס מייצג שורת תוכן במקרו */
typedef struct MacroLine {
    char* line;                  /* השורה עצמה */
    struct MacroLine* next;     /* מצביע לשורה הבאה */
} MacroLine;

/* טיפוס מייצג מקרו (שם + רשימת שורות) */
typedef struct {
    char name[MAX_NAME_LENGTH];  /* שם המקרו */
    MacroLine* lines;            /* רשימת שורות של המקרו */
} Macro;

/* טבלה המכילה את כל המקרואים שהוגדרו */
typedef struct {
    Macro macros[MAX_MACROS];           /* מערך מקרואים */
    int count;                          /* כמות מקרואים בטבלה */
    char macroNames[MAX_MACROS][MAX_NAME_LENGTH];  /* שמות למניעת כפילויות */
    int macroNameCount;                /* כמות שמות בשימוש */
    int errorFlag;                     /* דגל שגיאה – 1 אם הייתה שגיאה */
} MacroTable;

/*
    אתחול טבלת המקרואים לפני עיבוד
*/
void initMacroTable(MacroTable* table);

/*
    התחלת הגדרת מקרו – מקבל את שם המקרו ומוודא שהוא חוקי
*/
void startMacroDefinition(MacroTable* table, const char* rawInput);

/*
    סיום הגדרת מקרו (נכון לעכשיו – פונקציה ריקה)
*/
void endMacroDefinition(MacroTable* table);

/*
    הוספת שורת תוכן למקרו מסוים
*/
void addMacroContent(MacroTable* table, const char* name, const char* line);

/*
    חיפוש מקרו לפי שם – מחזיר מצביע אם נמצא, NULL אם לא
*/
Macro* findMacro(MacroTable* table, const char* name);

/*
    הרחבת מקרו – כותב את שורות התוכן של המקרו לקובץ פלט
*/
void expandMacro(FILE* outFile, Macro* macro);

/*
    שחרור כל הזיכרון שהוקצה לטבלת המקרואים
*/
void freeMacroTable(MacroTable* table);

#endif
