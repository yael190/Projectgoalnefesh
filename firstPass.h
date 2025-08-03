#define _CRT_SECURE_NO_WARNINGS
#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include "table.h"  /* לשימוש ב-Label */
#include <stdio.h>

/*
    מבצע את המעבר הראשון על קובץ .am:
    - סורק שורות, מזהה תוויות, פקודות, הגדרות נתונים
    - בונה את טבלת הסמלים בהתאם
    - מדווח על שגיאות
    - אם נמצאו שגיאות – מחזיר 0, אחרת 1

    קלט:
    - fileName: שם קובץ בסיס (ללא סיומת)
    - labelT: מצביע למערך התוויות
    - sizeL: כמות התוויות

    פלט:
    - 0 אם נמצאו שגיאות, 1 אם הצליח
*/
int first_pass_file(const char* fileName, Label** labelT, int* sizeL,
    int* instruction_count, int* data_count);

#endif
