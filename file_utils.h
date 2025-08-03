#define _CRT_SECURE_NO_WARNINGS/* file_utils.h */
#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>

/*
פותחת קובץ לקריאה (סיומת .am).
מחזירה מצביע לקובץ אם הצליח, אחרת NULL.
*/
FILE* open_am_file(const char* base_name);

/*
יוצרת שם קובץ חדש עם סיומת מתאימה (לדוגמה .ob, .ent, .ext).
מאחסנת את השם במערך היעד.
*/
void build_filename(char* dest, const char* base_name, const char* extension);

/*
פותחת קובץ לכתיבה. אם זו הפעם הראשונה – יוצר קובץ חדש.
*/
FILE* open_output_file(const char* base_name, const char* extension);

/*
סוגרת קובץ אם הוא פתוח.
*/
void safe_close(FILE* fp);

#endif
