#ifndef CHECKFUNC_H
#define CHECKFUNC_H

/*
   בדיקות תחביריות לפקודות שונות בהתאם למספר האופראנדים שלהן.
   כל פונקציה מקבלת שורת קלט (line) ובודקת האם התחביר תקין בהתאם לסוג הפקודה.
   מחזירה 0 אם אין שגיאות, 1 אם נמצאה שגיאה.
*/

/* בודק פקודות עם שני אופראנדים (mov, add, sub וכו') */
int check_mov_add_sub(char* line);

/* בודק פקודות עם אופראנד אחד (clr, not, inc, וכו') */
int check_clr_not_inc_dec_red(char* line);

/* בודק פקודות ללא אופראנדים (rts, stop) */
int check_rts_stop(char* line);

#endif
