#ifndef CHECK_H
#define CHECK_H

#include "table.h"

int isLabel(const char* word);
int isListSaveWord(const char* word);
int isValidInteger(const char* word);
int checkString(const char* str);
int checkData(const char* line, int* dataValues, int* DC);

/* בדיקה אם מחרוזת היא פקודת אסמבלי חוקית */
int isInstruction(const char* word);

#endif
