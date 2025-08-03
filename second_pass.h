#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include "encode_instruction.h"  /* בשביל Symbol */

/*
    מבצע את שלב המעבר השני:
    - קורא את קובץ .am
    - מזהה פקודות .entry ומעדכן את טבלת הסמלים
    - מקודד הוראות לפי טבלת הסמלים
    - יוצר קבצי פלט .ob, .ent, .ext

    פרמטרים:
    - base_name: שם בסיס של הקובץ (ללא סיומת)
    - symbol_table: טבלת הסמלים שנבנתה במעבר ראשון
    - symbol_count: כמות הסמלים בטבלה
    - instruction_count: מספר הוראות
    - data_count: מספר פריטי נתונים

    אין ערך מוחזר – קבצי הפלט נוצרים או נמחקים בהתאם לשגיאות.
*/
void second_pass(const char* base_name, Symbol* symbol_table, int symbol_count, int instruction_count, int data_count);

#endif
