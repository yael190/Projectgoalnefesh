#include <string.h>
#include "reserved.h"

#define RESERVED_KEYWORDS_COUNT 28

/* רשימת כל המילים השמורות: פקודות, הנחיות ורגיסטרים */
static const char* reservedWords[RESERVED_KEYWORDS_COUNT] = {
    "mov", "cmp", "add", "sub", "lea",
    "clr", "not", "inc", "dec",
    "jmp", "bne", "jsr",
    "red", "prn", "rts", "stop",
    ".data", ".string", ".entry", ".extern",
    "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"
};

/* בודק האם המחרוזת name מופיעה ברשימת המילים השמורות */
int isReservedKeyword(const char* name) {
    for (int i = 0; i < RESERVED_KEYWORDS_COUNT; i++) {
        if (strcmp(name, reservedWords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
