#define _CRT_SECURE_NO_WARNINGS
#ifndef RESERVED_H
#define RESERVED_H

/* בודק אם מילה היא מילת שמורה (פקודה, הנחיה או רגיסטר) */
int isReservedKeyword(const char* name);

#endif
