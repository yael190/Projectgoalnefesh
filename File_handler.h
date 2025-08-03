#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "macro_handler.h" /* עבור טיפוס MacroTable */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    קורא שמות קבצים מתוך קובץ input.txt,
    ומחזיר מערך מחרוזות של שמות קבצים ללא הסיומת.
    קולט מצביע למשתנה fileCount שמכיל את מספר הקבצים שנקראו.
    מחזיר NULL במקרה של שגיאה.
*/
char** read_file_list(const char* filename, int* fileCount);

/*
    מבצע קדם-עיבוד (preprocess) על כל הקבצים שברשימה,
    כולל זיהוי מקרואים, הרחבתם, ויצירת קבצי .am
*/
void preprocess_files(MacroTable* table, char** fileNames, int fileCount);


/*
    מבצע עיבוד מקרואים על קובץ קלט בודד עם סיומת .as
    ויוצר קובץ פלט עם סיומת .am
*/
void process_file(MacroTable* table, const char* fileName);



#endif
