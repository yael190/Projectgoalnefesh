#define _CRT_SECURE_NO_WARNINGS/* finalize_output.h */
#ifndef FINALIZE_OUTPUT_H
#define FINALIZE_OUTPUT_H

#include "encode_instruction.h"

/*
פונקציה זו ממירה מחרוזת בינארית (בת 14 סיביות) להצגה בהקסדצימלי.
מקבלת מחרוזת בינארית ומחזירה מחרוזת הקסדצימלית חדשה.
*/
char* binary_to_hex(const char* binary);

/*
פונקציה זו מאחדת את טבלאות ההוראות והנתונים ויוצרת קובץ .ob סופי.
היא מקבלת:
- base_name: שם בסיס של הקובץ
- instructions: מערך מחרוזות בינאריות של ההוראות
- icf: מספר הוראות סופי
- data: מערך מחרוזות בינאריות של הנתונים
- dcf: מספר נתונים סופי

הפלט הוא קובץ ob מסודר.
*/
void write_final_ob_file(const char* base_name, char** instructions, int icf, char** data, int dcf);

/*
פונקציה זו משחררת זיכרון מכל מערך מחרוזות דינמי.
*/
void free_string_array(char** array, int size);

#endif
