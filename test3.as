mcro .data   ; שם לא חוקי - לא אמור לעבוד
    mov r5, r6
mcroend

mcro PRINT_NUM
    prn r3
mcroend
mcro PRINT_NUM  ; מקרו כפול - אמור להיות שגיאה
    prn r4
mcroend

HELLO:
    PRINT_NUM
    stop
