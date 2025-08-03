#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "checkFunc.h"
#include "error_handler.h"
#include "string_utils.h"

/* בודק פקודות עם שני אופראנדים (mov, add, sub וכו') */
int check_mov_add_sub(char* line) {
    char* source = NULL, * comma = NULL, * destination = NULL, * extra = NULL;
    char* line_ptr = line;

    source = read_word(&line_ptr);
    comma = read_word(&line_ptr);
    destination = read_word(&line_ptr);
    extra = read_word(&line_ptr);

    if (source == NULL || comma == NULL || destination == NULL) {
        report_error("שגיאה: חסרים אופראנדים בפקודה", -1);
        goto cleanup;
    }

    if (strcmp(comma, ",") != 0) {
        report_error("שגיאה: חסר פסיק בין אופראנדים", -1);
        goto cleanup;
    }

    if (extra != NULL) {
        report_error("שגיאה: יותר מדי אופראנדים", -1);
        goto cleanup;
    }

    free(source); free(comma); free(destination);
    if (extra) free(extra);
    return 0;

cleanup:
    if (source) free(source);
    if (comma) free(comma);
    if (destination) free(destination);
    if (extra) free(extra);
    return 1;
}

/* בודק פקודות עם אופראנד אחד בלבד (clr, not, inc וכו') */
int check_clr_not_inc_dec_red(char* line) {
    char* operand = NULL, * extra = NULL;
    char* line_ptr = line;

    operand = read_word(&line_ptr);
    extra = read_word(&line_ptr);

    if (!operand) {
        report_error("שגיאה: חסר אופראנד בפקודה", -1);
        if (extra) free(extra);
        return 1;
    }

    if (extra) {
        report_error("שגיאה: יותר מדי אופראנדים", -1);
        free(operand);
        free(extra);
        return 1;
    }

    free(operand);
    return 0;
}

/* בודק פקודות ללא אופראנדים (rts, stop) */
int check_rts_stop(char* line) {
    char* token = read_word(&line);
    if (token != NULL) {
        report_error("שגיאה: פקודה זו לא מקבלת אופראנדים", -1);
        free(token);
        return 1;
    }
    return 0;
}
