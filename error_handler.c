/* error_handler.c */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "error_handler.h"

/* ����� ����� ����� �� ������ ����� ����� */
static int error_flag = 0;

/* ������ �� ����� ������� �� ������ �� ���� ���� (�� ����). */
void report_error(const char* message, int line_number) {
    if (!message) return;
    if (line_number > 0)
        fprintf(stderr, "����� (���� %d): %s\n", line_number, message);
    else
        fprintf(stderr, "�����: %s\n", message);
    error_flag = 1;
}

/* ������ ��� ������ ����� ����� ���. */
int has_errors() {
    return error_flag;
}

/* ����� �� ��� ������ (��� ������ ���� ���). */
void reset_errors() {
    error_flag = 0;
}

/* ������ ����� ������ �� �� ������ */
void print_errors() {
    if (error_flag) {
        fprintf(stderr, "\n����� ������ ����� �����. �� ����� �� ������� �����.\n");
    }
}
