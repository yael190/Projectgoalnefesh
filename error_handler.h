/* error_handler.h */
#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

/*
מדווחת על שגיאה על ידי הדפסת הודעה, ושומרת שהתרחשה שגיאה.
ניתן להעביר גם מספר שורה (או -1 אם לא רלוונטי).
*/
void report_error(const char* message, int line_number);

/*
בודקת האם דווחה לפחות שגיאה אחת עד כה.
*/
int has_errors();

/*
מאפסת את מצב השגיאות (שימושי כשמעבדים קובץ חדש).
*/
void reset_errors();
void print_errors();


#endif
