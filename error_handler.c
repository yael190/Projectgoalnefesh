/* error_handler.c */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "error_handler.h"

/* משתנה פנימי שמסמן אם התרחשה שגיאה כלשהי */
static int error_flag = 0;

/* מדווחת על שגיאה ומדפיסה את ההודעה עם מספר שורה (אם ידוע). */
void report_error(const char* message, int line_number) {
    if (!message) return;
    if (line_number > 0)
        fprintf(stderr, "שגיאה (שורה %d): %s\n", line_number, message);
    else
        fprintf(stderr, "שגיאה: %s\n", message);
    error_flag = 1;
}

/* מחזירה האם התרחשה לפחות שגיאה אחת. */
int has_errors() {
    return error_flag;
}

/* מאפסת את דגל השגיאה (כדי להתחיל מעבר חדש). */
void reset_errors() {
    error_flag = 0;
}

/* מדפיסה הודעה מרוכזת אם יש שגיאות */
void print_errors() {
    if (error_flag) {
        fprintf(stderr, "\nאירעו שגיאות במהלך הריצה. נא לבדוק את ההודעות למעלה.\n");
    }
}
